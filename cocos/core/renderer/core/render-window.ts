import {
    GFXTextureType,
    GFXTextureUsageBit,
    GFXFormat,
} from '../../gfx/define';
import { GFXRenderPass, GFXTexture, GFXFramebuffer, GFXRenderPassInfo, GFXDevice, GFXTextureInfo, GFXFramebufferInfo } from '../../gfx';
import { Root } from '../../root';
import { RenderWindowHandle, RenderWindowPool, RenderWindowView, FramebufferPool, NULL_HANDLE } from './memory-pools';

export interface IRenderWindowInfo {
    title?: string;
    width: number;
    height: number;
    renderPassInfo: GFXRenderPassInfo;
    swapchainBufferIndices?: number;
    shouldSyncSizeWithSwapchain?: boolean;
}

/**
 * @en The render window represents the render target, it could be an off screen frame buffer or the on screen buffer.
 * @zh 渲染窗口代表了一个渲染目标，可以是离屏的帧缓冲，也可以是屏幕缓冲
 */
export class RenderWindow {

    /**
     * @en Get window width.
     * @zh 窗口宽度。
     */
    get width (): number {
        return this._width;
    }

    /**
     * @en Get window height.
     * @zh 窗口高度。
     */
    get height (): number {
        return this._height;
    }

    /**
     * @en Get window frame buffer.
     * @zh 帧缓冲对象。
     */
    get framebuffer (): GFXFramebuffer {
        return FramebufferPool.get(RenderWindowPool.get(this._poolHandle, RenderWindowView.FRAMEBUFFER));
    }

    get shouldSyncSizeWithSwapchain () {
        return this._shouldSyncSizeWithSwapchain;
    }

    /**
     * @en Whether it has on screen attachments
     * @zh 这个渲染窗口是否指向在屏缓冲
     */
    get hasOnScreenAttachments () {
        return RenderWindowPool.get(this._poolHandle, RenderWindowView.HAS_ON_SCREEN_ATTACHMENTS) === 1 ? true : false;
    }

    /**
     * @en Whether it has off screen attachments
     * @zh 这个渲染窗口是否指向离屏缓冲
     */
    get hasOffScreenAttachments () {
        return RenderWindowPool.get(this._poolHandle, RenderWindowView.HAS_OFF_SCREEN_ATTACHMENTS) === 1 ? true : false;
    }

    get handle () : RenderWindowHandle {
        return this._poolHandle;
    }

    /**
     * @private
     */
    public static registerCreateFunc (root: Root) {
        root._createWindowFun = (_root: Root): RenderWindow => new RenderWindow(_root);
    }

    protected _title: string = '';
    protected _width: number = 1;
    protected _height: number = 1;
    protected _nativeWidth: number = 1;
    protected _nativeHeight: number = 1;
    protected _renderPass: GFXRenderPass | null = null;
    protected _colorTextures: (GFXTexture | null)[] = [];
    protected _depthStencilTexture: GFXTexture | null = null;
    protected _swapchainBufferIndices = 0;
    protected _shouldSyncSizeWithSwapchain = false;
    protected _poolHandle: RenderWindowHandle = NULL_HANDLE;

    private constructor (root: Root) {
    }

    public initialize (device: GFXDevice, info: IRenderWindowInfo): boolean {
        this._poolHandle = RenderWindowPool.alloc();

        if (info.title !== undefined) {
            this._title = info.title;
        }

        if (info.swapchainBufferIndices !== undefined) {
            this._swapchainBufferIndices = info.swapchainBufferIndices;
        }

        if (info.shouldSyncSizeWithSwapchain !== undefined) {
            this._shouldSyncSizeWithSwapchain = info.shouldSyncSizeWithSwapchain;
        }

        this._width = info.width;
        this._height = info.height;
        this._nativeWidth = this._width;
        this._nativeHeight = this._height;

        const { colorAttachments, depthStencilAttachment } = info.renderPassInfo;
        for (let i = 0; i < colorAttachments.length; i++) {
            if (colorAttachments[i].format === GFXFormat.UNKNOWN) {
                colorAttachments[i].format = device.colorFormat;
            }
        }
        if (depthStencilAttachment && depthStencilAttachment.format === GFXFormat.UNKNOWN) {
            depthStencilAttachment.format = device.depthStencilFormat;
        }

        this._renderPass = device.createRenderPass(info.renderPassInfo);

        for (let i = 0; i < colorAttachments.length; i++) {
            let colorTex: GFXTexture | null = null;
            if (!(this._swapchainBufferIndices & (1 << i))) {
                colorTex = device.createTexture(new GFXTextureInfo(
                    GFXTextureType.TEX2D,
                    GFXTextureUsageBit.COLOR_ATTACHMENT | GFXTextureUsageBit.SAMPLED,
                    colorAttachments[i].format,
                    this._width,
                    this._height,
                ));
                RenderWindowPool.set(this._poolHandle, RenderWindowView.HAS_OFF_SCREEN_ATTACHMENTS, 1);
            } else {
                RenderWindowPool.set(this._poolHandle, RenderWindowView.HAS_ON_SCREEN_ATTACHMENTS, 1);
            }
            this._colorTextures.push(colorTex);
        }

        // Use the sign bit to indicate depth attachment
        if (depthStencilAttachment) {
            if (this._swapchainBufferIndices >= 0) {
                this._depthStencilTexture = device.createTexture(new GFXTextureInfo(
                    GFXTextureType.TEX2D,
                    GFXTextureUsageBit.DEPTH_STENCIL_ATTACHMENT | GFXTextureUsageBit.SAMPLED,
                    depthStencilAttachment.format,
                    this._width,
                    this._height,
                ));
                RenderWindowPool.set(this._poolHandle, RenderWindowView.HAS_OFF_SCREEN_ATTACHMENTS, 1);
            } else {
                RenderWindowPool.set(this._poolHandle, RenderWindowView.HAS_ON_SCREEN_ATTACHMENTS, 1);
            }
        }

        const hFBO = FramebufferPool.alloc(device, new GFXFramebufferInfo(
            this._renderPass,
            this._colorTextures,
            this._depthStencilTexture,
        ));
        RenderWindowPool.set(this._poolHandle, RenderWindowView.FRAMEBUFFER, hFBO);

        return true;
    }

    public destroy () {
        if (this._depthStencilTexture) {
            this._depthStencilTexture.destroy();
            this._depthStencilTexture = null;
        }

        for (let i = 0; i < this._colorTextures.length; i++) {
            const colorTexture = this._colorTextures[i];
            if (colorTexture) {
                colorTexture.destroy();
            }
        }
        this._colorTextures.length = 0;

        if (this._poolHandle) {
            FramebufferPool.get(RenderWindowPool.get(this._poolHandle, RenderWindowView.FRAMEBUFFER)).destroy();
            this._poolHandle = NULL_HANDLE;
        }
    }

    /**
     * @en Resize window.
     * @zh 重置窗口大小。
     * @param width The new width.
     * @param height The new height.
     */
    public resize (width: number, height: number) {
        this._width = width;
        this._height = height;

        if (width > this._nativeWidth ||
            height > this._nativeHeight) {

            this._nativeWidth = width;
            this._nativeHeight = height;

            let needRebuild = false;

            if (this._depthStencilTexture) {
                this._depthStencilTexture.resize(width, height);
                needRebuild = true;
            }

            for (let i = 0; i < this._colorTextures.length; i++) {
                const colorTex = this._colorTextures[i];
                if (colorTex) {
                    colorTex.resize(width, height);
                    needRebuild = true;
                }
            }

            const framebuffer = FramebufferPool.get(RenderWindowPool.get(this._poolHandle, RenderWindowView.FRAMEBUFFER));
            if (needRebuild && framebuffer) {
                framebuffer.destroy();
                framebuffer.initialize(new GFXFramebufferInfo(
                    this._renderPass!,
                    this._colorTextures,
                    this._depthStencilTexture,
                ));
            }
        }
    }
}