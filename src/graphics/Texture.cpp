#include "Texture.hpp"

#include <png.h>
#include <stdexcept>
#include <fstream>
#include <vector>

#include "gl/gl.h"

namespace tetrablocks::graphics {

    namespace detail {

        inline int toGL(const TextureWrap wrap) {
            switch (wrap) {
                case TextureWrap::Repeat:
                    return GL_REPEAT;
                case TextureWrap::RepeatMirror:
                    return GL_MIRRORED_REPEAT;
                case TextureWrap::ClampEdge:
                    return GL_CLAMP_TO_EDGE;
                case TextureWrap::ClampBorder:
                    return GL_CLAMP_TO_BORDER;
            }
            return -1;
        }

        inline int toGL(const TextureFilter filter) {
            switch (filter) {
                case TextureFilter::Linear:
                    return GL_LINEAR;
                case TextureFilter::Nearest:
                    return GL_NEAREST;
            }
            return -1;
        }

        inline int toGL(const TextureMinFilter filter) {
            switch (filter) {
                case TextureMinFilter::NearestLinear:
                    return GL_NEAREST_MIPMAP_LINEAR;
                case TextureMinFilter::NearestNearest:
                    return GL_NEAREST_MIPMAP_NEAREST;
                case TextureMinFilter::LinearLinear:
                    return GL_LINEAR_MIPMAP_LINEAR;
                case TextureMinFilter::LinearNearest:
                    return GL_LINEAR_MIPMAP_NEAREST;
            }
            return -1;
        }

        inline int toGL(const TextureFormat format) {
            switch (format) {
                case TextureFormat::RGBA:
                    return GL_RGBA;
                case TextureFormat::RGB:
                    return GL_RGB;
                case TextureFormat::Mono:
                    return GL_RED;
            }
            return -1;
        }

    }

    void Texture::loadPNG(const std::string& path) {
        FILE* fp = fopen(path.c_str(), "rb");
        if (!fp)
            throw std::runtime_error("Failed to open PNG file.");

        png_byte header[8];
        fread(header, 1, 8, fp);
        if (png_sig_cmp(header, 0, 8))
            throw std::runtime_error("Not a PNG file.");

        png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!png)
            throw std::runtime_error("png_create_read_struct failed.");

        png_infop info = png_create_info_struct(png);
        if (!info)
            throw std::runtime_error("png_create_info_struct failed.");

        if (_setjmp (*png_set_longjmp_fn(png, longjmp, sizeof (jmp_buf))))
            throw std::runtime_error("Error during PNG creation.");

        png_init_io(png, fp);
        png_set_sig_bytes(png, 8);

        png_read_info(png, info);

        const uint width = png_get_image_width(png, info);
        const uint height = png_get_image_height(png, info);
        const png_byte color_type = png_get_color_type(png, info);
        const png_byte bit_depth = png_get_bit_depth(png, info);

        if (bit_depth == 16)
            png_set_strip_16(png);

        if (color_type == PNG_COLOR_TYPE_PALETTE)
            png_set_palette_to_rgb(png);

        if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
            png_set_expand_gray_1_2_4_to_8(png);

        if (png_get_valid(png, info, PNG_INFO_tRNS))
            png_set_tRNS_to_alpha(png);

        if (color_type == PNG_COLOR_TYPE_RGB ||
            color_type == PNG_COLOR_TYPE_GRAY ||
            color_type == PNG_COLOR_TYPE_PALETTE)
            png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

        if (color_type == PNG_COLOR_TYPE_GRAY ||
            color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
            png_set_gray_to_rgb(png);

        png_read_update_info(png, info);

        std::vector<png_byte> imageData(png_get_rowbytes(png, info) * height);
        std::vector<png_bytep> row_pointers(height);
        for (int y = 0; y < height; y++) {
            row_pointers[y] = imageData.data() + y * png_get_rowbytes(png, info);
        }

        png_read_image(png, row_pointers.data());

        fclose(fp);
        png_destroy_read_struct(&png, &info, nullptr);

        alloc(static_cast<int>(width),static_cast<int>(height),TextureFormat::RGBA,imageData.data());
    }

    void Texture::deinit() {
        glDeleteTextures(1,&m_handle);
        m_size = {0,0};
    }

    void Texture::alloc(const int w, const int h,TextureFormat format, const void* buffer){
        if (m_handle != 0) {
            deinit();
        }
        glGenTextures(1, &m_handle);
        glBindTexture(GL_TEXTURE_2D,m_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, detail::toGL(format), w, h, 0, detail::toGL(format), GL_UNSIGNED_BYTE, buffer);
        m_size = {w,h};
    }

    void Texture::subdata(const int x, const int y, const int w, const int h, const TextureFormat format, const void* buffer) const {
        if (m_handle != 0){
            glTexSubImage2D(GL_TEXTURE_2D,0,x,y,w,h,detail::toGL(format),GL_UNSIGNED_BYTE, buffer);
        }
    }

    void Texture::setWrap(const TextureWrap st) const {
        setWrap(st,st);
    }

    void Texture::setWrap(const TextureWrap s, const TextureWrap t) const {
        if (m_handle != 0){
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, detail::toGL(s));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, detail::toGL(t));
        }
    }

    void Texture::setMinFilter(const TextureFilter f) const {
        if (m_handle != 0) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, detail::toGL(f));
        }
    }

    void Texture::setMinFilter(const TextureMinFilter f) const {
        if (m_handle != 0) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, detail::toGL(f));
        }
    }

    void Texture::setMagFilter(const TextureFilter f) const {
        if (m_handle != 0) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, detail::toGL(f));
        }
    }

    void Texture::setBorder(const glm::vec4& color) const {
        if (m_handle != 0) {
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &color[0]);
        }
    }

    void Texture::genMipmaps() const {
        if (m_handle != 0) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }

    void Texture::bind(u_int8_t slot) const {
        if (slot >= 16) {
            slot = 0;
        }
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D,m_handle);
    }

    [[nodiscard]] uint Texture::getHandle() const{
        return m_handle;
    }

    [[nodiscard]] glm::uvec2 Texture::getSize() const{
        return m_size;
    }

}
