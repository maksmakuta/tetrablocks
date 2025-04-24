#include "tetrablocks/graphics/Texture.hpp"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/vector_relational.hpp>

#include "glad/gl.h"
#include "lodePNG/lodepng.h"

namespace tetrablocks {

    namespace internal {

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

    
    Texture::Texture(const std::string& path) : m_size(0), m_handle(0){
        std::vector<unsigned char> image;
        unsigned width, height;
        if(const unsigned error = lodepng::decode(image, width, height, path); error != 0) {
            std::cout << "Loading image error " << error << ": " << lodepng_error_text(error) << std::endl;
            return;
        }
        alloc(static_cast<int>(width),static_cast<int>(height),TextureFormat::RGBA,image.data());
    }

    void Texture::alloc(const int w, const int h, const TextureFormat format, const void* buffer){
        if (m_handle != 0) {
            glDeleteTextures(1,&m_handle);
            m_size = {0,0};
        }
        glGenTextures(1, &m_handle);
        glBindTexture(GL_TEXTURE_2D,m_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, internal::toGL(format), w, h, 0, internal::toGL(format), GL_UNSIGNED_BYTE, buffer);
        m_size = {w,h};
    }

    Texture::~Texture() {
        glDeleteTextures(1,&m_handle);
        m_size = {0,0};
    }

    void Texture::subdata(const int x, const int y, const int w, const int h, const TextureFormat format, const void* buffer) const {
        if (m_handle != 0){
            glTexSubImage2D(GL_TEXTURE_2D,0,x,y,w,h,internal::toGL(format),GL_UNSIGNED_BYTE, buffer);
        }
    }

    void Texture::setWrap(const TextureWrap st) const {
        setWrap(st,st);
    }

    void Texture::setWrap(const TextureWrap s, const TextureWrap t) const {
        if (m_handle != 0){
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, internal::toGL(s));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, internal::toGL(t));
        }
    }

    void Texture::setMinFilter(const TextureFilter f) const {
        if (m_handle != 0) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, internal::toGL(f));
        }
    }

    void Texture::setMinFilter(const TextureMinFilter f) const {
        if (m_handle != 0) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, internal::toGL(f));
        }
    }

    void Texture::setMagFilter(const TextureFilter f) const {
        if (m_handle != 0) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, internal::toGL(f));
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
    
    glm::vec2 Texture::getSize() const{
        return m_size;
    }

    glm::uint Texture::getID() const {
        return m_handle;
    }
}
