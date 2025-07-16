#include "blend_modes.h"

u_int32_t blend_colors(u_int32_t dst, u_int32_t src, BlendMode mode) {
    // TODO: these need to be done for RGB colors

    switch (mode) {
    case BLEND_REPLACE:
        return src;
    case BLEND_ADD:
        return dst + src;
    case BLEND_MULTIPLY:
        return (((float) dst / 255.0) * ((float) src / 255.0)) * 255.0;
    case BLEND_MAX:
        if (src > dst)
            return src;
        return dst;
    }
}
