#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace tetrablocks {


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
        Texture();
        explicit Texture(const std::string& path);
        ~Texture();

        void alloc(int w, int h, TextureFormat format,const void* buffer = nullptr);
        void dealloc();

        void subdata(int x, int y,int w, int h, TextureFormat format, const void* buffer) const;
        void setWrap(TextureWrap st) const;
        void setWrap(TextureWrap s,TextureWrap t) const;
        void setBorder(const glm::vec4& color) const;
        void setMinFilter(TextureFilter) const;
        void setMinFilter(TextureMinFilter) const;
        void setMagFilter(TextureFilter) const;
        void genMipmaps() const;

        void bind(u_int8_t slot = 0) const;
        void saveTo(const std::string& filename);

        [[nodiscard]] glm::uvec2 getSize() const;
        [[nodiscard]] glm::uint getID() const;
    private:
        glm::uvec2 m_size;
        glm::uint m_handle;
        uint8_t m_bpp;

    };

}

#endif //TEXTURE_HPP
