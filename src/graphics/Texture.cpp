#include "Texture.hpp"

#include <spng.h>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/vector_relational.hpp>

#include "gl/gl.hpp"

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
        if (!fp) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return;
        }
        spng_ctx* ctx = spng_ctx_new(0);
        if (!ctx) {
            std::cerr << "Failed to create spng context" << std::endl;
            fclose(fp);
            return;
        }
        spng_set_png_file(ctx, fp);
        spng_ihdr ihdr{};
        if (spng_get_ihdr(ctx, &ihdr) != 0) {
            std::cerr << "Failed to get PNG header" << std::endl;
            spng_ctx_free(ctx);
            fclose(fp);
            return;

        }
        const size_t img_size = ihdr.width * ihdr.height * 4; // RGBA
        std::vector<uint8_t> img_data(img_size);
        if (spng_decode_image(ctx, img_data.data(), img_size, SPNG_FMT_RGBA8, 0) != 0) {
            std::cerr << "Failed to decode PNG image" << std::endl;
            spng_ctx_free(ctx);
            fclose(fp);
            return;
        }

        alloc(ihdr.width, ihdr.height, TextureFormat::RGBA,img_data.data());

        spng_ctx_free(ctx);
        fclose(fp);

    }

    void Texture::deinit() {
        glDeleteTextures(1,&m_handle);
        m_size = {0,0};
    }

    void Texture::alloc(const int w, const int h, const TextureFormat format, const void* buffer){
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
