//
//  jsb_conversions.cpp
//  cocos2d_js_bindings
//
//  Created by James Chen on 5/17/17.
//
//

#include "jsb_conversions.hpp"

// seval to native

bool seval_to_int32(const se::Value& v, int32_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toInt32(); //FIXME: need to check isNan?
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_uint32(const se::Value& v, uint32_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toUint32();
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_int8(const se::Value& v, int8_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toInt8();
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_uint8(const se::Value& v, uint8_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toUint8();
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_int16(const se::Value& v, int16_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toInt16();
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_uint16(const se::Value& v, uint16_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toUint16();
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_boolean(const se::Value& v, bool* ret)
{
    assert(ret != nullptr);
    if (v.isBoolean())
    {
        *ret = v.toBoolean();
        return true;
    }

    if (v.isNumber())
    {
        *ret = v.toInt32() != 0 ? true : false;
        return true;
    }
    *ret = false;
    return false;
}

bool seval_to_float(const se::Value& v, float* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toFloat();
        return true;
    }
    *ret = 0.0f;
    return false;
}

bool seval_to_double(const se::Value& v, double* ret)
{
    if (v.isNumber())
    {
        *ret = v.toNumber();
        return true;
    }
    *ret = 0.0;
    return false;
}

bool seval_to_long(const se::Value& v, long* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toLong();
        return true;
    }
    *ret = 0L;
    return false;
}

bool seval_to_ulong(const se::Value& v, unsigned long* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toUlong();
        return true;
    }
    *ret = 0UL;
    return false;
}

bool seval_to_longlong(const se::Value& v, long long* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = (long long)v.toLong();
        return true;
    }
    *ret = 0LL;
    return false;
}

bool seval_to_ssize(const se::Value& v, ssize_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = (ssize_t)v.toLong();
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_std_string(const se::Value& v, std::string* ret)
{
    assert(ret != nullptr);
    if (v.isString())
    {
        *ret = v.toString();
        return true;
    }
    ret->clear();
    return false;
}

bool seval_to_Vec2(const se::Value& v, cocos2d::Vec2* pt)
{
    assert(v.isObject() && pt != nullptr);
    se::Object* obj = v.toObject();
    se::Value x;
    se::Value y;
    bool ok = obj->getProperty("x", &x);
    JSB_PRECONDITION3(ok && x.isNumber(), false, *pt = cocos2d::Vec2::ZERO);
    ok = obj->getProperty("y", &y);
    JSB_PRECONDITION3(ok && y.isNumber(), false, *pt = cocos2d::Vec2::ZERO);
    pt->x = x.toFloat();
    pt->y = y.toFloat();
    return true;
}

bool seval_to_Vec3(const se::Value& v, cocos2d::Vec3* pt)
{
    assert(v.isObject() && pt != nullptr);
    se::Object* obj = v.toObject();
    se::Value x;
    se::Value y;
    se::Value z;
    bool ok = obj->getProperty("x", &x);
    JSB_PRECONDITION3(ok && x.isNumber(), false, *pt = cocos2d::Vec3::ZERO);
    ok = obj->getProperty("y", &y);
    JSB_PRECONDITION3(ok && y.isNumber(), false, *pt = cocos2d::Vec3::ZERO);
    ok = obj->getProperty("z", &z);
    JSB_PRECONDITION3(ok && z.isNumber(), false, *pt = cocos2d::Vec3::ZERO);
    pt->x = x.toFloat();
    pt->y = y.toFloat();
    pt->z = z.toFloat();
    return true;
}

bool seval_to_Vec4(const se::Value& v, cocos2d::Vec4* pt)
{
    assert(v.isObject() && pt != nullptr);
    pt->x = pt->y = pt->z = pt->w = 0.0f;
    se::Object* obj = v.toObject();
    se::Value x;
    se::Value y;
    se::Value z;
    se::Value w;
    bool ok = obj->getProperty("x", &x);
    JSB_PRECONDITION3(ok && x.isNumber(), false, *pt = cocos2d::Vec4::ZERO);
    ok = obj->getProperty("y", &y);
    JSB_PRECONDITION3(ok && y.isNumber(), false, *pt = cocos2d::Vec4::ZERO);
    ok = obj->getProperty("z", &z);
    JSB_PRECONDITION3(ok && z.isNumber(), false, *pt = cocos2d::Vec4::ZERO);
    ok = obj->getProperty("w", &w);
    JSB_PRECONDITION3(ok && w.isNumber(), false, *pt = cocos2d::Vec4::ZERO);
    pt->x = x.toFloat();
    pt->y = y.toFloat();
    pt->z = z.toFloat();
    pt->w = w.toFloat();
    return true;
}

bool seval_to_Mat4(const se::Value& v, cocos2d::Mat4* mat)
{
    assert(v.isObject() && mat != nullptr);

    JSB_PRECONDITION3(v.toObject()->isArray(), false, *mat = cocos2d::Mat4::IDENTITY;);

    se::Object* obj = v.toObject();

    bool ok = false;
    uint32_t len = 0;
    ok = obj->getArrayLength(&len);
    JSB_PRECONDITION3(ok, false, *mat = cocos2d::Mat4::IDENTITY);

    if (len != 16)
    {
        SE_REPORT_ERROR("Array length error: %d, was expecting 16", len);
        *mat = cocos2d::Mat4::IDENTITY;
        return false;
    }

    se::Value tmp;
    for (uint32_t i = 0; i < len; ++i)
    {
        ok = obj->getArrayElement(i, &tmp);
        JSB_PRECONDITION3(ok, false, *mat = cocos2d::Mat4::IDENTITY);

        if (tmp.isNumber())
        {
            mat->m[i] = tmp.toFloat();
        }
        else
        {
            SE_REPORT_ERROR("%u, not supported type in matrix", i);
            *mat = cocos2d::Mat4::IDENTITY;
            return false;
        }

        tmp.setUndefined();
    }

    return true;
}

bool seval_to_Size(const se::Value& v, cocos2d::Size* size)
{
    assert(v.isObject() && size != nullptr);
    se::Object* obj = v.toObject();
    se::Value width;
    se::Value height;

    bool ok = obj->getProperty("width", &width);
    JSB_PRECONDITION3(ok && width.isNumber(), false, *size = cocos2d::Size::ZERO);
    ok = obj->getProperty("height", &height);
    JSB_PRECONDITION3(ok && height.isNumber(), false, *size = cocos2d::Size::ZERO);
    size->width = width.toFloat();
    size->height = height.toFloat();
    return true;
}

bool seval_to_Rect(const se::Value& v, cocos2d::Rect* rect)
{
    assert(v.isObject() && rect != nullptr);
    se::Object* obj = v.toObject();
    se::Value x;
    se::Value y;
    se::Value width;
    se::Value height;

    bool ok = obj->getProperty("x", &x);
    JSB_PRECONDITION3(ok && x.isNumber(), false, *rect = cocos2d::Rect::ZERO);
    ok = obj->getProperty("y", &y);
    JSB_PRECONDITION3(ok && y.isNumber(), false, *rect = cocos2d::Rect::ZERO);
    ok = obj->getProperty("width", &width);
    JSB_PRECONDITION3(ok && width.isNumber(), false, *rect = cocos2d::Rect::ZERO);
    ok = obj->getProperty("height", &height);
    JSB_PRECONDITION3(ok && height.isNumber(), false, *rect = cocos2d::Rect::ZERO);
    rect->origin.x = x.toFloat();
    rect->origin.y = y.toFloat();
    rect->size.width = width.toFloat();
    rect->size.height = height.toFloat();

    return true;
}

bool seval_to_Color3B(const se::Value& v, cocos2d::Color3B* color)
{
    assert(v.isObject() && color != nullptr);
    se::Object* obj = v.toObject();
    se::Value r;
    se::Value g;
    se::Value b;
    bool ok = obj->getProperty("r", &r);
    JSB_PRECONDITION3(ok && r.isNumber(), false, *color = cocos2d::Color3B::BLACK);
    ok = obj->getProperty("g", &g);
    JSB_PRECONDITION3(ok && g.isNumber(), false, *color = cocos2d::Color3B::BLACK);
    ok = obj->getProperty("b", &b);
    JSB_PRECONDITION3(ok && b.isNumber(), false, *color = cocos2d::Color3B::BLACK);
    color->r = (GLubyte)r.toUint16();
    color->g = (GLubyte)g.toUint16();
    color->b = (GLubyte)b.toUint16();
    return true;
}

bool seval_to_Color4B(const se::Value& v, cocos2d::Color4B* color)
{
    assert(v.isObject() && color != nullptr);
    se::Object* obj = v.toObject();
    se::Value r;
    se::Value g;
    se::Value b;
    se::Value a;
    bool ok = obj->getProperty("r", &r);
    JSB_PRECONDITION3(ok && r.isNumber(), false, *color = cocos2d::Color4B::BLACK);
    ok = obj->getProperty("g", &g);
    JSB_PRECONDITION3(ok && g.isNumber(), false, *color = cocos2d::Color4B::BLACK);
    ok = obj->getProperty("b", &b);
    JSB_PRECONDITION3(ok && b.isNumber(), false, *color = cocos2d::Color4B::BLACK);
    ok = obj->getProperty("a", &a);
    JSB_PRECONDITION3(ok && b.isNumber(), false, *color = cocos2d::Color4B::BLACK);
    color->r = (GLubyte)r.toUint16();
    color->g = (GLubyte)g.toUint16();
    color->b = (GLubyte)b.toUint16();
    color->a = (GLubyte)a.toUint16();
    return true;
}

bool seval_to_Color4F(const se::Value& v, cocos2d::Color4F* color)
{
    assert(v.isObject() && color != nullptr);
    se::Object* obj = v.toObject();
    se::Value r;
    se::Value g;
    se::Value b;
    se::Value a;
    bool ok = obj->getProperty("r", &r);
    JSB_PRECONDITION3(ok && r.isNumber(), false, *color = cocos2d::Color4F::BLACK);
    ok = obj->getProperty("g", &g);
    JSB_PRECONDITION3(ok && g.isNumber(), false, *color = cocos2d::Color4F::BLACK);
    ok = obj->getProperty("b", &b);
    JSB_PRECONDITION3(ok && b.isNumber(), false, *color = cocos2d::Color4F::BLACK);
    ok = obj->getProperty("a", &a);
    JSB_PRECONDITION3(ok && b.isNumber(), false, *color = cocos2d::Color4F::BLACK);
    color->r = r.toFloat() / 255.0f;
    color->g = g.toFloat() / 255.0f;
    color->b = b.toFloat() / 255.0f;
    color->a = a.toFloat() / 255.0f;
    return true;
}

bool seval_to_ccvalue(const se::Value& v, cocos2d::Value* ret)
{
    assert(ret != nullptr);
    bool ok = true;
    if (v.isObject())
    {
        se::Object* jsobj = v.toObject();
        if (!jsobj->isArray())
        {
            // It's a normal js object.
            cocos2d::ValueMap dictVal;
            ok = seval_to_ccvaluemap(v, &dictVal);
            JSB_PRECONDITION3(ok, false, *ret = cocos2d::Value::Null);
            *ret = cocos2d::Value(dictVal);
        }
        else
        {
            // It's a js array object.
            cocos2d::ValueVector arrVal;
            ok = seval_to_ccvaluevector(v, &arrVal);
            JSB_PRECONDITION3(ok, false, *ret = cocos2d::Value::Null);
            *ret = cocos2d::Value(arrVal);
        }
    }
    else if (v.isString())
    {
        *ret = v.toString();
    }
    else if (v.isNumber())
    {
        *ret = v.toNumber();
    }
    else if (v.isBoolean())
    {
        *ret = v.toBoolean();
    }
    else
    {
        CCASSERT(false, "not supported type");
    }

    return ok;
}

bool seval_to_ccvaluemap(const se::Value& v, cocos2d::ValueMap* ret)
{
    assert(ret != nullptr);

    if (v.isNullOrUndefined())
    {
        ret->clear();
        return true;
    }

    assert(v.isObject());

    JSB_PRECONDITION3(!v.isNullOrUndefined(), false, ret->clear());

    se::Object* obj = v.toObject();

    cocos2d::ValueMap& dict = *ret;

    std::vector<std::string> allKeys;
    JSB_PRECONDITION3(obj->getAllKeys(&allKeys), false, ret->clear());

    bool ok = false;
    se::Value value;
    cocos2d::Value ccvalue;
    for (const auto& key : allKeys)
    {
        JSB_PRECONDITION3(obj->getProperty(key.c_str(), &value), false, ret->clear());
        ok = seval_to_ccvalue(value, &ccvalue);
        JSB_PRECONDITION3(ok, false, ret->clear());
        dict.emplace(key, ccvalue);
    }

    return true;
}

static bool isNumberString(const std::string& str)
{
    for (const auto& c : str)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

bool seval_to_ccvaluemapintkey(const se::Value& v, cocos2d::ValueMapIntKey* ret)
{
    assert(ret != nullptr);
    if (v.isNullOrUndefined())
    {
        ret->clear();
        return true;
    }

    assert(v.isObject());

    JSB_PRECONDITION3(!v.isNullOrUndefined(), false, ret->clear());

    se::Object* obj = v.toObject();

    cocos2d::ValueMapIntKey& dict = *ret;

    std::vector<std::string> allKeys;
    JSB_PRECONDITION3(obj->getAllKeys(&allKeys), false, ret->clear());

    bool ok = false;
    se::Value value;
    cocos2d::Value ccvalue;
    for (const auto& key : allKeys)
    {
        JSB_PRECONDITION3(obj->getProperty(key.c_str(), &value), false, ret->clear());

        if (!isNumberString(key))
        {
            CCLOGWARN("seval_to_ccvaluemapintkey, found not numeric key: %s", key.c_str());
            continue;
        }

        int intKey = atoi(key.c_str());

        ok = seval_to_ccvalue(value, &ccvalue);
        JSB_PRECONDITION3(ok, false, ret->clear());
        dict.emplace(intKey, ccvalue);
    }
    
    return true;
}

bool seval_to_ccvaluevector(const se::Value& v,  cocos2d::ValueVector* ret)
{
    assert(ret != nullptr);

    assert(v.isObject());

    se::Object* obj = v.toObject();
    JSB_PRECONDITION3(obj->isArray(), false, ret->clear());

    uint32_t len = 0;
    obj->getArrayLength(&len);

    bool ok = false;
    se::Value value;
    cocos2d::Value ccvalue;
    for (uint32_t i = 0; i < len; ++i)
    {
        if (obj->getArrayElement(i, &value))
        {
            ok = seval_to_ccvalue(value, &ccvalue);
            JSB_PRECONDITION3(ok, false, ret->clear());
            ret->push_back(ccvalue);
        }
    }
    
    return true;
}

bool sevals_variadic_to_ccvaluevector(const se::ValueArray& args, cocos2d::ValueVector* ret)
{
    bool ok = false;
    cocos2d::Value ccvalue;

    for (const auto& arg : args)
    {
        ok = seval_to_ccvalue(arg, &ccvalue);
        JSB_PRECONDITION3(ok, false, ret->clear());
        ret->push_back(ccvalue);
    }

    return true;
}

bool seval_to_blendfunc(const se::Value& v, cocos2d::BlendFunc* ret)
{
    assert(v.isObject());
    se::Object* obj = v.toObject();
    se::Value value;
    bool ok = false;

    ok = obj->getProperty("src", &value);
    JSB_PRECONDITION3(ok, false, *ret = cocos2d::BlendFunc::DISABLE);
    ret->src = value.toUint32();
    ok = obj->getProperty("dst", &value);
    JSB_PRECONDITION3(ok, false, *ret = cocos2d::BlendFunc::DISABLE);

    ret->dst = value.toUint32();
    return true;
}

bool seval_to_std_vector_string(const se::Value& v, std::vector<std::string>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    assert(obj->isArray());
    uint32_t len = 0;
    if (obj->getArrayLength(&len))
    {
        se::Value value;
        for (uint32_t i = 0; i < len; ++i)
        {
            JSB_PRECONDITION3(obj->getArrayElement(i, &value), false, ret->clear());
            assert(value.isString());
            ret->push_back(value.toString());
        }
        return true;
    }

    ret->clear();
    return false;
}

bool seval_to_std_vector_int(const se::Value& v, std::vector<int>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    assert(obj->isArray());
    uint32_t len = 0;
    if (obj->getArrayLength(&len))
    {
        se::Value value;
        for (uint32_t i = 0; i < len; ++i)
        {
            JSB_PRECONDITION3(obj->getArrayElement(i, &value), false, ret->clear());
            assert(value.isNumber());
            ret->push_back(value.toInt32());
        }
        return true;
    }

    ret->clear();
    return false;
}

bool seval_to_std_vector_float(const se::Value& v, std::vector<float>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    assert(obj->isArray());
    uint32_t len = 0;
    if (obj->getArrayLength(&len))
    {
        se::Value value;
        for (uint32_t i = 0; i < len; ++i)
        {
            JSB_PRECONDITION3(obj->getArrayElement(i, &value), false, ret->clear());
            assert(value.isNumber());
            ret->push_back(value.toFloat());
        }
        return true;
    }

    ret->clear();
    return false;
}

bool seval_to_std_vector_Vec2(const se::Value& v, std::vector<cocos2d::Vec2>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    assert(obj->isArray());
    uint32_t len = 0;
    if (obj->getArrayLength(&len))
    {
        se::Value value;
        cocos2d::Vec2 pt;
        for (uint32_t i = 0; i < len; ++i)
        {
            JSB_PRECONDITION3(obj->getArrayElement(i, &value) && seval_to_Vec2(value, &pt), false, ret->clear());
            ret->push_back(pt);
        }
        return true;
    }

    ret->clear();
    return false;
}

bool seval_to_std_map_string_string(const se::Value& v, std::map<std::string, std::string>* ret)
{
    assert(ret != nullptr);

    if (v.isNullOrUndefined())
    {
        ret->clear();
        return true;
    }

    assert(v.isObject());

    JSB_PRECONDITION3(!v.isNullOrUndefined(), false, ret->clear());

    se::Object* obj = v.toObject();

    std::vector<std::string> allKeys;
    JSB_PRECONDITION3(obj->getAllKeys(&allKeys), false, ret->clear());

    bool ok = false;
    se::Value value;
    std::string strValue;
    for (const auto& key : allKeys)
    {
        JSB_PRECONDITION3(obj->getProperty(key.c_str(), &value), false, ret->clear());
        ok = seval_to_std_string(value, &strValue);
        JSB_PRECONDITION3(ok, false, ret->clear());
        ret->emplace(key, strValue);
    }
    
    return true;
}

bool seval_to_FontDefinition(const se::Value& v, cocos2d::FontDefinition* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();

    // default values
    const char* defautlFontName = "Arial";
    const int defaultFontSize = 32;
    cocos2d::TextHAlignment defaultTextAlignment = cocos2d::TextHAlignment::LEFT;
    cocos2d::TextVAlignment defaultTextVAlignment = cocos2d::TextVAlignment::TOP;

    // by default shadow and stroke are off
    ret->_shadow._shadowEnabled = false;
    ret->_stroke._strokeEnabled = false;

    // white text by default
    ret->_fontFillColor = cocos2d::Color3B::WHITE;

    se::Value tmp, tmp2;

    // font name
    if (obj->getProperty("fontName", &tmp) && tmp.isString())
    {
        if (tmp.toString().empty())
        {
            ret->_fontName = defautlFontName;
        }
        else
        {
            ret->_fontName = tmp.toString();
        }
    }
    else
    {
        ret->_fontName = defautlFontName;
    }

    // font size
    if (obj->getProperty("fontSize", &tmp) && tmp.isNumber())
    {
        ret->_fontSize = tmp.toInt32();
    }
    else
    {
        ret->_fontSize = defaultFontSize;
    }

    // font alignment horizontal
    if (obj->getProperty("textAlign", &tmp) && tmp.isNumber())
    {
        ret->_alignment = (cocos2d::TextHAlignment)tmp.toInt32();
    }
    else
    {
        ret->_alignment = defaultTextAlignment;
    }

    // font alignment vertical
    if (obj->getProperty("verticalAlign", &tmp) && tmp.isNumber())
    {
        ret->_vertAlignment = (cocos2d::TextVAlignment)tmp.toInt32();
    }
    else
    {
        ret->_vertAlignment = defaultTextVAlignment;
    }

    // font fill color
    if (obj->getProperty("fillStyle", &tmp) && tmp.isObject())
    {
        seval_to_Color3B(tmp, &ret->_fontFillColor);
    }

    // font rendering box dimensions
    if (obj->getProperty("boundingWidth", &tmp) && tmp.isNumber()
        && obj->getProperty("boundingHeight", &tmp2) && tmp2.isNumber())
    {
        ret->_dimensions.width = tmp.toFloat();
        ret->_dimensions.height = tmp2.toFloat();
    }

    // shadow
    if (obj->getProperty("shadowEnabled", &tmp) && tmp.isBoolean())
    {
        ret->_shadow._shadowEnabled = tmp.toBoolean();

        if (ret->_shadow._shadowEnabled)
        {
            // default shadow values
            ret->_shadow._shadowOffset  = cocos2d::Size(5, 5);
            ret->_shadow._shadowBlur    = 1;
            ret->_shadow._shadowOpacity = 1;

            // shadow offset
            if (obj->getProperty("shadowOffsetX", &tmp) && tmp.isNumber()
                && obj->getProperty("shadowOffsetY", &tmp2) && tmp2.isNumber())
            {
                ret->_shadow._shadowOffset.width = tmp.toFloat();
                ret->_shadow._shadowOffset.height = tmp2.toFloat();
            }

            // shadow blur
            if (obj->getProperty("shadowBlur", &tmp) && tmp.isNumber())
            {
                ret->_shadow._shadowBlur = tmp.toNumber();
            }

            // shadow intensity
            if (obj->getProperty("shadowOpacity", &tmp) && tmp.isNumber())
            {
                ret->_shadow._shadowOpacity = tmp.toNumber();
            }
        }
    }

    // stroke
    if (obj->getProperty("strokeEnabled", &tmp) && tmp.isBoolean())
    {
        ret->_stroke._strokeEnabled = tmp.toBoolean();
        if (ret->_stroke._strokeEnabled)
        {
            // default stroke values
            ret->_stroke._strokeSize  = 1;
            ret->_stroke._strokeColor = cocos2d::Color3B::BLUE;

            // stroke color
            if (obj->getProperty("strokeStyle", &tmp) && tmp.isObject())
            {
                seval_to_Color3B(tmp, &ret->_stroke._strokeColor);
            }

            // stroke size
            if (obj->getProperty("lineWidth", &tmp) && tmp.isNumber())
            {
                ret->_stroke._strokeSize = tmp.toNumber();
            }

            // stroke alpha
            if (obj->getProperty("strokeAlpha", &tmp) && tmp.isNumber())
            {
                ret->_stroke._strokeAlpha = tmp.toUint8();
            }
        }
    }

    return true;
}

bool seval_to_Acceleration(const se::Value& v, cocos2d::Acceleration* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    bool ok = false;
    se::Value tmp;

    ok = obj->getProperty("x", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, ret->x = ret->y = ret->z = ret->timestamp = 0.0);
    ret->x = tmp.toNumber();

    ok = obj->getProperty("y", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, ret->x = ret->y = ret->z = ret->timestamp = 0.0);
    ret->y = tmp.toNumber();

    ok = obj->getProperty("z", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, ret->x = ret->y = ret->z = ret->timestamp = 0.0);
    ret->z = tmp.toNumber();

    ok = obj->getProperty("timestamp", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, ret->x = ret->y = ret->z = ret->timestamp = 0.0);
    ret->timestamp = tmp.toNumber();

    return true;
}

bool seval_to_Quaternion(const se::Value& v, cocos2d::Quaternion* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    bool ok = false;
    se::Value tmp;

    ok = obj->getProperty("x", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = cocos2d::Quaternion::ZERO);
    ret->x = tmp.toFloat();

    ok = obj->getProperty("y", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = cocos2d::Quaternion::ZERO);
    ret->y = tmp.toFloat();

    ok = obj->getProperty("z", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = cocos2d::Quaternion::ZERO);
    ret->z = tmp.toFloat();

    ok = obj->getProperty("w", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = cocos2d::Quaternion::ZERO);
    ret->w = tmp.toFloat();

    return true;
}

bool seval_to_AffineTransform(const se::Value& v, cocos2d::AffineTransform* ret)
{
    static cocos2d::AffineTransform ZERO = {0, 0, 0, 0, 0, 0};

    assert(ret != nullptr);
    assert(v.isObject());
    se::Value tmp;
    se::Object* obj = v.toObject();
    bool ok = false;

    ok = obj->getProperty("a", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->a = tmp.toFloat();

    ok = obj->getProperty("b", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->b = tmp.toFloat();

    ok = obj->getProperty("c", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->c = tmp.toFloat();

    ok = obj->getProperty("d", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->d = tmp.toFloat();

    ok = obj->getProperty("tx", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->tx = tmp.toFloat();

    ok = obj->getProperty("ty", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->ty = tmp.toFloat();

    return true;
}

bool seval_to_Viewport(const se::Value& v, cocos2d::experimental::Viewport* ret)
{
    static cocos2d::experimental::Viewport ZERO = {0, 0, 0, 0};

    assert(ret != nullptr);
    assert(v.isObject());
    se::Value tmp;
    se::Object* obj = v.toObject();
    bool ok = false;

    ok = obj->getProperty("left", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->_left = tmp.toFloat();

    ok = obj->getProperty("bottom", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->_bottom = tmp.toFloat();

    ok = obj->getProperty("width", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->_width = tmp.toFloat();

    ok = obj->getProperty("height", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->_height = tmp.toFloat();

    return true;
}

bool seval_to_Data(const se::Value& v, cocos2d::Data* ret)
{
    assert(ret != nullptr);
    assert(v.isObject() && v.toObject()->isTypedArray());
    uint8_t* ptr = nullptr;
    size_t length = 0;
    bool ok = v.toObject()->getTypedArrayData(&ptr, &length);
    if (ok)
    {
        ret->copy(ptr, length);
    }
    else
    {
        ret->clear();
    }

    return ok;
}

bool seval_to_DownloaderHints(const se::Value& v, cocos2d::network::DownloaderHints* ret)
{
    static cocos2d::network::DownloaderHints ZERO = {0, 0, ""};
    assert(ret != nullptr);
    assert(v.isObject());
    se::Value tmp;
    se::Object* obj = v.toObject();
    bool ok = false;

    ok = obj->getProperty("countOfMaxProcessingTasks", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->countOfMaxProcessingTasks = tmp.toUint32();

    ok = obj->getProperty("timeoutInSeconds", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->timeoutInSeconds = tmp.toUint32();

    ok = obj->getProperty("tempFileNameSuffix", &tmp);
    JSB_PRECONDITION3(ok && tmp.isString(), false, *ret = ZERO);
    ret->tempFileNameSuffix = tmp.toString();

    return ok;
}

bool seval_to_ResourceData(const se::Value& v, cocos2d::ResourceData* ret)
{
    static cocos2d::ResourceData ZERO;
    assert(ret != nullptr);
    assert(v.isObject());
    se::Value tmp;
    se::Object* obj = v.toObject();
    bool ok = false;

    ok = obj->getProperty("type", &tmp);
    JSB_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
    ret->type = tmp.toInt32();

    ok = obj->getProperty("name", &tmp);
    JSB_PRECONDITION3(ok && tmp.isString(), false, *ret = ZERO);
    ret->file = tmp.toString();

    ok = obj->getProperty("plist", &tmp);
    JSB_PRECONDITION3(ok && tmp.isString(), false, *ret = ZERO);
    ret->plist = tmp.toString();

    return ok;
}

bool seval_to_TTFConfig(const se::Value& v, cocos2d::TTFConfig* ret)
{
    assert(false); //FIXME:
    return true;
}

bool seval_to_b2Vec2(const se::Value& v, b2Vec2* ret)
{
    assert(false); //FIXME:
    return true;
}

bool seval_to_b2AABB(const se::Value& v, b2AABB* ret)
{
    assert(false); //FIXME:
    return true;
}

//////////////////////////////////////////////////////////////////////////////////
// native to seval

bool int32_to_seval(int32_t v, se::Value* ret)
{
    ret->setInt32(v);
    return true;
}

bool uint32_to_seval(uint32_t v, se::Value* ret)
{
    ret->setUint32(v);
    return true;
}

bool int16_to_seval(uint16_t v, se::Value* ret)
{
    ret->setInt16(v);
    return true;
}

bool uint16_to_seval(uint16_t v, se::Value* ret)
{
    ret->setUint16(v);
    return true;
}

bool int8_to_seval(int8_t v, se::Value* ret)
{
    ret->setInt8(v);
    return true;
}

bool uint8_to_seval(uint8_t v, se::Value* ret)
{
    ret->setUint8(v);
    return true;
}

bool boolean_to_seval(bool v, se::Value* ret)
{
    ret->setBoolean(v);
    return true;
}

bool float_to_seval(float v, se::Value* ret)
{
    ret->setFloat(v);
    return true;
}

bool double_to_seval(double v, se::Value* ret)
{
    ret->setNumber(v);
    return true;
}

bool long_to_seval(long v, se::Value* ret)
{
    ret->setLong(v);
    return true;
}

bool ulong_to_seval(unsigned long v, se::Value* ret)
{
    ret->setUlong(v);
    return true;
}

bool longlong_to_seval(long long v, se::Value* ret)
{
    ret->setLong((long)v);
    return true;
}

bool ssize_to_seval(ssize_t v, se::Value* ret)
{
    ret->setLong((long)v);
    return true;
}

bool std_string_to_seval(const std::string& v, se::Value* ret)
{
    ret->setString(v);
    return true;
}

bool Vec2_to_seval(const cocos2d::Vec2& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool Vec3_to_seval(const cocos2d::Vec3& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    obj->setProperty("z", se::Value(v.z));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool Vec4_to_seval(const cocos2d::Vec4& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    obj->setProperty("z", se::Value(v.z));
    obj->setProperty("w", se::Value(v.w));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool Mat4_to_seval(const cocos2d::Mat4& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createArrayObject(16, false);

    for (uint8_t i = 0; i < 16; ++i)
    {
        obj->setArrayElement(i, se::Value(v.m[i]));
    }

    ret->setObject(obj);
    obj->release();
    return true;
}

bool Size_to_seval(const cocos2d::Size& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("width", se::Value(v.width));
    obj->setProperty("height", se::Value(v.height));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool Rect_to_seval(const cocos2d::Rect& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("x", se::Value(v.origin.x));
    obj->setProperty("y", se::Value(v.origin.y));
    obj->setProperty("width", se::Value(v.size.width));
    obj->setProperty("height", se::Value(v.size.height));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool Color3B_to_seval(const cocos2d::Color3B& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("r", se::Value(v.r));
    obj->setProperty("g", se::Value(v.g));
    obj->setProperty("b", se::Value(v.b));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool Color4B_to_seval(const cocos2d::Color4B& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("r", se::Value(v.r));
    obj->setProperty("g", se::Value(v.g));
    obj->setProperty("b", se::Value(v.b));
    obj->setProperty("a", se::Value(v.a));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool Color4F_to_seval(const cocos2d::Color4F& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("r", se::Value(v.r));
    obj->setProperty("g", se::Value(v.g));
    obj->setProperty("b", se::Value(v.b));
    obj->setProperty("a", se::Value(v.a));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool ccvalue_to_seval(const cocos2d::Value& v, se::Value* ret)
{
    assert(ret != nullptr);
    bool ok = true;
    switch (v.getType())
    {
        case cocos2d::Value::Type::BOOLEAN:
            ret->setBoolean(v.asBool());
            break;
        case cocos2d::Value::Type::FLOAT:
        case cocos2d::Value::Type::DOUBLE:
            ret->setNumber(v.asDouble());
            break;
        case cocos2d::Value::Type::INTEGER:
            ret->setInt32(v.asInt());
            break;
        case cocos2d::Value::Type::STRING:
            ret->setString(v.asString());
            break;
        case cocos2d::Value::Type::VECTOR:
            ok = ccvaluevector_to_seval(v.asValueVector(), ret);
            break;
        case cocos2d::Value::Type::MAP:
            ok = ccvaluemap_to_seval(v.asValueMap(), ret);
            break;
        case cocos2d::Value::Type::INT_KEY_MAP:
            ok = ccvaluemapintkey_to_seval(v.asIntKeyMap(), ret);
            break;
        default:
            ok = false;
            break;
    }

    return ok;
}

bool ccvaluemap_to_seval(const cocos2d::ValueMap& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);
    bool ok = true;
    for (const auto& e : v)
    {
        const std::string& key = e.first;
        const cocos2d::Value& value = e.second;

        if (key.empty())
            continue;

        se::Value tmp;
        if (!ccvalue_to_seval(value, &tmp))
        {
            ok = false;
            ret->setUndefined();
            break;
        }

        obj->setProperty(key.c_str(), tmp);
    }
    if (ok)
        ret->setObject(obj);
    obj->release();

    return ok;
}

bool ccvaluemapintkey_to_seval(const cocos2d::ValueMapIntKey& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);
    bool ok = true;
    for (const auto& e : v)
    {
        std::stringstream keyss;
        keyss << e.first;
        std::string key = keyss.str();
        const cocos2d::Value& value = e.second;

        if (key.empty())
            continue;

        se::Value tmp;
        if (!ccvalue_to_seval(value, &tmp))
        {
            ok = false;
            ret->setUndefined();
            break;
        }

        obj->setProperty(key.c_str(), tmp);
    }
    if (ok)
        ret->setObject(obj);
    obj->release();

    return ok;
}

bool ccvaluevector_to_seval(const cocos2d::ValueVector& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createArrayObject(v.size(), false);
    bool ok = true;

    uint32_t i = 0;
    for (const auto& value : v)
    {
        se::Value tmp;
        if (!ccvalue_to_seval(value, &tmp))
        {
            ok = false;
            ret->setUndefined();
            break;
        }

        obj->setArrayElement(i, tmp);
        ++i;
    }
    if (ok)
        ret->setObject(obj);
    obj->release();
    return ok;
}

bool blendfunc_to_seval(const cocos2d::BlendFunc& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("src", se::Value(v.src));
    obj->setProperty("dst", se::Value(v.dst));
    ret->setObject(obj);
    obj->release();

    return true;
}

namespace {

    template<typename T>
    bool std_vector_T_to_seval(const std::vector<T>& v, se::Value* ret)
    {
        assert(ret != nullptr);
        se::Object* obj = se::Object::createArrayObject(v.size(), true);
        bool ok = true;

        uint32_t i = 0;
        for (const auto& value : v)
        {
            if (!obj->setArrayElement(i, se::Value(value)))
            {
                ok = false;
                ret->setUndefined();
                break;
            }
            ++i;
        }

        if (ok)
            ret->setObject(obj);
        obj->switchToUnrooted();
        obj->release();
        return ok;
    }

}

bool std_vector_string_to_seval(const std::vector<std::string>& v, se::Value* ret)
{
    return std_vector_T_to_seval(v, ret);
}

bool std_vector_int_to_seval(const std::vector<int>& v, se::Value* ret)
{
    return std_vector_T_to_seval(v, ret);
}

bool std_vector_float_to_seval(const std::vector<float>& v, se::Value* ret)
{
    return std_vector_T_to_seval(v, ret);
}

bool std_vector_Touch_to_seval(const std::vector<cocos2d::Touch*>& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* arr = se::Object::createArrayObject(v.size(), true);

    uint32_t i = 0;
    se::Value tmp;
    bool ok = true;
    for (const auto& touch : v)
    {
        if (!native_ptr_to_seval<cocos2d::Touch>(touch, &tmp))
        {
            ok = false;
            break;
        }
        arr->setArrayElement(i, tmp);
        ++i;
    }
    if (ok)
        ret->setObject(arr);
    else
        ret->setUndefined();
    arr->switchToUnrooted();
    arr->release();
    return ok;
}

bool std_map_string_string_to_seval(const std::map<std::string, std::string>& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);
    bool ok = true;
    for (const auto& e : v)
    {
        const std::string& key = e.first;
        const std::string& value = e.second;

        if (key.empty())
            continue;

        se::Value tmp;
        if (!std_string_to_seval(value, &tmp))
        {
            ok = false;
            ret->setUndefined();
            break;
        }

        obj->setProperty(key.c_str(), tmp);
    }

    if (ok)
        ret->setObject(obj);
    obj->release();
    
    return ok;
}

//FIXME: why v has to be a pointer?
bool uniform_to_seval(const cocos2d::Uniform* v, se::Value* ret)
{
    assert(v != nullptr && ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("location", se::Value(v->location));
    obj->setProperty("size", se::Value(v->size));
    obj->setProperty("type", se::Value(v->type));
    obj->setProperty("name", se::Value(v->name));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool FontDefinition_to_seval(const cocos2d::FontDefinition& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Value tmp;

    se::Object* obj = se::Object::createPlainObject(false);
    bool ok = true;
    do
    {
        obj->setProperty("fontName", se::Value(v._fontName));
        obj->setProperty("fontSize", se::Value(v._fontSize));
        obj->setProperty("textAlign", se::Value((int32_t)v._alignment));
        obj->setProperty("verticalAlign", se::Value((int32_t)v._vertAlignment));

        if (!Color3B_to_seval(v._fontFillColor, &tmp))
        {
            ok = false;
            break;
        }
        obj->setProperty("fillStyle", tmp);
        obj->setProperty("boundingWidth", se::Value(v._dimensions.width));
        obj->setProperty("boundingHeight", se::Value(v._dimensions.height));

        obj->setProperty("shadowEnabled", se::Value(v._shadow._shadowEnabled));
        obj->setProperty("shadowOffsetX", se::Value(v._shadow._shadowOffset.width));
        obj->setProperty("shadowOffsetY", se::Value(v._shadow._shadowOffset.height));
        obj->setProperty("shadowBlur", se::Value(v._shadow._shadowBlur));
        obj->setProperty("shadowOpacity", se::Value(v._shadow._shadowOpacity));

        obj->setProperty("strokeEnabled", se::Value(v._stroke._strokeEnabled));
        if (!Color3B_to_seval(v._stroke._strokeColor, &tmp))
        {
            ok = false;
            break;
        }

        obj->setProperty("strokeStyle", tmp);
        obj->setProperty("lineWidth", se::Value(v._stroke._strokeSize));
        obj->setProperty("strokeAlpha", se::Value(v._stroke._strokeAlpha));
    } while (false);

    ret->setObject(obj);
    obj->release();

    return ok;
}

//FIXME: why v has to be a pointer?
bool Acceleration_to_seval(const cocos2d::Acceleration* v, se::Value* ret)
{
    assert(v != nullptr && ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("x", se::Value(v->x));
    obj->setProperty("y", se::Value(v->y));
    obj->setProperty("z", se::Value(v->z));
    obj->setProperty("timestamp", se::Value(v->timestamp));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool Quaternion_to_seval(const cocos2d::Quaternion& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    obj->setProperty("z", se::Value(v.z));
    obj->setProperty("w", se::Value(v.w));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool ManifestAsset_to_seval(const cocos2d::extension::ManifestAsset& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("md5", se::Value(v.md5));
    obj->setProperty("path", se::Value(v.path));
    obj->setProperty("compressed", se::Value(v.compressed));
    obj->setProperty("size", se::Value(v.size));
    obj->setProperty("downloadState", se::Value(v.downloadState));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool AffineTransform_to_seval(const cocos2d::AffineTransform& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("a", se::Value(v.a));
    obj->setProperty("b", se::Value(v.b));
    obj->setProperty("c", se::Value(v.c));
    obj->setProperty("d", se::Value(v.d));
    obj->setProperty("tx", se::Value(v.tx));
    obj->setProperty("ty", se::Value(v.ty));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool Viewport_to_seval(const cocos2d::experimental::Viewport& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("left", se::Value(v._left));
    obj->setProperty("bottom", se::Value(v._bottom));
    obj->setProperty("width", se::Value(v._width));
    obj->setProperty("height", se::Value(v._height));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool Data_to_seval(const cocos2d::Data& v, se::Value* ret)
{
    assert(ret != nullptr);
    assert(!v.isNull());
    se::Object* obj = se::Object::createUint8TypedArray(v.getBytes(), v.getSize(), false);
    ret->setObject(obj);
    obj->release();
    return true;
}

bool DownloadTask_to_seval(const cocos2d::network::DownloadTask& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("identifier", se::Value(v.identifier));
    obj->setProperty("requestURL", se::Value(v.requestURL));
    obj->setProperty("storagePath", se::Value(v.storagePath));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool ResourceData_to_seval(const cocos2d::ResourceData& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("type", se::Value(v.type));
    obj->setProperty("file", se::Value(v.file));
    obj->setProperty("plist", se::Value(v.plist));
    ret->setObject(obj);
    obj->release();

    return true;
}

// Spine conversions
bool speventdata_to_seval(const spEventData& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);
    obj->setProperty("name", se::Value(v.name));
    obj->setProperty("intValue", se::Value(v.intValue));
    obj->setProperty("floatValue", se::Value(v.floatValue));
    obj->setProperty("stringValue", se::Value(v.stringValue));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool spevent_to_seval(const spEvent& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);

    se::Value dataVal;
    JSB_PRECONDITION3(speventdata_to_seval(*v.data, &dataVal), false, ret->setUndefined());
    obj->setProperty("data", dataVal);
    obj->setProperty("time", se::Value(v.time));
    obj->setProperty("intValue", se::Value(v.intValue));
    obj->setProperty("floatValue", se::Value(v.floatValue));
    obj->setProperty("stringValue", se::Value(v.stringValue));
    ret->setObject(obj);
    obj->release();

    return true;
}

bool spbonedata_to_seval(const spBoneData& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);

    // root haven't parent
    se::Value parentVal;
    if (0 != strcmp(v.name, "root") && v.parent)
    {
        JSB_PRECONDITION3(spbonedata_to_seval(*v.parent, &parentVal), false, ret->setUndefined());
    }

    obj->setProperty("index", se::Value(v.index));
    obj->setProperty("name", se::Value(v.name));
    obj->setProperty("parent", parentVal);
    obj->setProperty("length", se::Value(v.length));
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    obj->setProperty("rotation", se::Value(v.rotation));
    obj->setProperty("scaleX", se::Value(v.scaleX));
    obj->setProperty("scaleY", se::Value(v.scaleY));
    obj->setProperty("shearX", se::Value(v.shearX));
    obj->setProperty("shearY", se::Value(v.shearY));
    obj->setProperty("transformMode", se::Value(v.transformMode));

    ret->setObject(obj);
    obj->release();

    return true;
}

bool spbone_to_seval(const spBone& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);

    // root haven't parent
    se::Value parentVal;
    if (0 != strcmp(v.data->name, "root") && v.parent)
    {
        JSB_PRECONDITION3(spbone_to_seval(*v.parent, &parentVal), false, ret->setUndefined());
    }

    se::Value data;
    JSB_PRECONDITION3(spbonedata_to_seval(*v.data, &data), false, ret->setUndefined());

    obj->setProperty("data", data);
    obj->setProperty("parent", parentVal);
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    obj->setProperty("rotation", se::Value(v.rotation));
    obj->setProperty("scaleX", se::Value(v.scaleX));
    obj->setProperty("scaleY", se::Value(v.scaleY));
    obj->setProperty("shearX", se::Value(v.shearX));
    obj->setProperty("shearY", se::Value(v.shearY));
    obj->setProperty("m00", se::Value(v.a));
    obj->setProperty("m01", se::Value(v.b));
    obj->setProperty("m10", se::Value(v.c));
    obj->setProperty("m11", se::Value(v.d));
    obj->setProperty("worldX", se::Value(v.worldX));
    obj->setProperty("worldY", se::Value(v.worldY));

    ret->setObject(obj);
    obj->release();

    return true;
}

bool spskeleton_to_seval(const spSkeleton& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);

    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    obj->setProperty("flipX", se::Value(v.flipX));
    obj->setProperty("flipY", se::Value(v.flipY));
    obj->setProperty("time", se::Value(v.time));
    obj->setProperty("boneCount", se::Value(v.bonesCount));
    obj->setProperty("slotCount", se::Value(v.slotsCount));

    ret->setObject(obj);
    obj->release();
    return true;
}

bool spattachment_to_seval(const spAttachment& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);

    obj->setProperty("name", se::Value(v.name));
    obj->setProperty("type", se::Value((int32_t)v.type));

    ret->setObject(obj);
    obj->release();
    return true;
}

bool spslotdata_to_seval(const spSlotData& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);

    se::Value boneData;
    JSB_PRECONDITION3(spbonedata_to_seval(*v.boneData, &boneData), false, ret->setUndefined());

    obj->setProperty("name", se::Value(v.name));
    obj->setProperty("attachmentName", se::Value(v.attachmentName));
    obj->setProperty("r", se::Value(v.r));
    obj->setProperty("g", se::Value(v.g));
    obj->setProperty("b", se::Value(v.b));
    obj->setProperty("a", se::Value(v.a));
    obj->setProperty("blendMode", se::Value((int32_t)v.blendMode));
    obj->setProperty("boneData", boneData);

    ret->setObject(obj);
    obj->release();
    return true;
}

bool spslot_to_seval(const spSlot& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);

    se::Value bone;
    JSB_PRECONDITION3(spbone_to_seval(*v.bone, &bone), false, ret->setUndefined());

    se::Value attachment;
    JSB_PRECONDITION3(spattachment_to_seval(*v.attachment, &attachment), false, ret->setUndefined());

    se::Value data;
    JSB_PRECONDITION3(spslotdata_to_seval(*v.data, &data), false, ret->setUndefined());

    obj->setProperty("r", se::Value(v.r));
    obj->setProperty("g", se::Value(v.g));
    obj->setProperty("b", se::Value(v.b));
    obj->setProperty("a", se::Value(v.a));
    obj->setProperty("bone", bone);
    obj->setProperty("attachment", attachment);
    obj->setProperty("data", data);

    ret->setObject(obj);
    obj->release();
    return true;
}

bool sptimeline_to_seval(const spTimeline& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);

    obj->setProperty("type", se::Value((int32_t)v.type));

    ret->setObject(obj);
    obj->release();
    return true;
}

bool spanimationstate_to_seval(const spAnimationState& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);

    obj->setProperty("timeScale", se::Value(v.timeScale));
    obj->setProperty("trackCount", se::Value(v.tracksCount));

    ret->setObject(obj);
    obj->release();
    return true;
}

bool spanimation_to_seval(const spAnimation& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::Object* obj = se::Object::createPlainObject(false);

    se::Value timelines;
    JSB_PRECONDITION3(sptimeline_to_seval(**v.timelines, &timelines), false, ret->setUndefined());

    obj->setProperty("name", se::Value(v.name));
    obj->setProperty("duration", se::Value(v.duration));
    obj->setProperty("timelineCount", se::Value(v.timelinesCount));
    obj->setProperty("timelines", timelines);

    ret->setObject(obj);
    obj->release();
    return true;
}

bool sptrackentry_to_seval(const spTrackEntry& v, se::Value* ret)
{
    return native_ptr_to_seval<spTrackEntry>((spTrackEntry*)&v, ret);
}

// Box2d
bool b2Vec2_to_seval(const b2Vec2& v, se::Value* ret)
{
    assert(false);//FIXME:
    return false;
}

bool b2Manifold_to_seval(const b2Manifold* v, se::Value* ret)
{
    assert(false);//FIXME:
    return false;
}

bool b2AABB_to_seval(const b2AABB& v, se::Value* ret)
{
    assert(false);//FIXME:
    return false;
}
