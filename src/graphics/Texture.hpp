#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace tetrablocks::graphics {

    enum class TextureWrap {
        Repeat,
        RepeatMirror,
        ClampEdge,
        ClampBorder
    };

    enum class TextureFilter {
        Linear,
        Nearest
    };

    enum class TextureMinFilter {
        LinearLinear,
        LinearNearest,
        NearestLinear,
        NearestNearest
    };

    enum class TextureFormat {
        RGBA,
        RGB,
        Mono
    };

    class Texture {
    public:
        Texture() = default;

        void loadPNG(const std::string& path);
        void deinit();

        void alloc(int w, int h, TextureFormat format,const void* buffer = nullptr);
        void subdata(int x, int y,int w, int h, TextureFormat format, const void* buffer) const;
        void setWrap(TextureWrap st) const;
        void setWrap(TextureWrap s,TextureWrap t) const;
        void setBorder(const glm::vec4& color) const;
        void setMinFilter(TextureFilter) const;
        void setMinFilter(TextureMinFilter) const;
        void setMagFilter(TextureFilter) const;
        void genMipmaps() const;

        void bind(u_int8_t slot = 0) const;

        [[nodiscard]] uint getHandle() const;
        [[nodiscard]] glm::uvec2 getSize() const;

    private:
        glm::uvec2 m_size{};
        uint m_handle{0};
    };

}

#endif //TEXTURE_HPP
