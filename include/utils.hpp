#pragma once
#include <kn/KrakenEngine.hpp>
#include <filesystem>

namespace fs = std::filesystem;

#include "TileManager.hpp"

namespace utils{
    struct minmax {
        float min, max;
    };

    inline void print() {
        std::cout << std::endl;
    }

    template<typename inp, typename... Args>
    inline void print(const inp& first, const Args&... rest) {
        std::cout << first;
        if constexpr (sizeof...(rest) > 0) {
            std::cout << ' ';
            print(rest...);
        } else {
            std::cout << std::endl;
        }
    }

    inline float starttime = SDL_GetTicks();
    inline float elapsedtime;
    inline int fps = 0;

    inline void outFPS(const bool p_print = true){
            float time = (SDL_GetTicks()-starttime)/1000;
            ++fps;
            if(p_print){
                // print((fps/time),fps,time);
                std::cout<<(fps/time)<<" "<<fps<<" "<<time<<"\n";
            }
    }

    inline std::vector<bool> generateAlphaMask(SDL_Surface* surface) {
        std::vector<bool> mask(surface->w * surface->h, false);

        Uint32* pixels = (Uint32*)surface->pixels;

        for (int y = 0; y < surface->h; ++y) {
            for (int x = 0; x < surface->w; ++x) {
                int index = y * surface->w + x;
                Uint32 pixel = pixels[index];

                Uint8 r, g, b, a;
                SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);

                mask[index] = (a > 0);
            }
        }

        return mask;
    }
    inline bool isRegionTransparent(const std::vector<bool>& mask, int texW,const kn::Rect& region) {
        for (int y = region.y; y < region.y + region.h; ++y) {
            for (int x = region.x; x < region.x + region.w; ++x) {
                int index = y * texW + x;
                if (mask[index]) return false;
            }
        }
        return true;
    }

    template<typename T_ptr>
    inline void deletePointerVector(const T_ptr& vec) {
        for (auto ptr : vec) {
            delete ptr;
        }
        vec.clear();
    }

    inline std::vector<kn::math::Vec2> getPolygonNormals(const std::vector<kn::math::Vec2>& polygon) {
        std::vector<kn::math::Vec2> result;
        size_t size = polygon.size();

        for (size_t i = 0; i < size; ++i) {
            const kn::math::Vec2& current = polygon[i];
            const kn::math::Vec2& next = polygon[(i + 1) % size];
            kn::math::Vec2 edge = next - current;
            kn::math::Vec2 normal = {0,0};
            if(edge.perpendicular().normalize())normal = kn::math::normalize(edge.perpendicular());
            result.push_back(normal);
        }

        return result;
    }

    inline minmax project(const std::vector<kn::math::Vec2>& polygon, const kn::math::Vec2& axis) {
        float min = kn::math::dot(polygon[0],axis);
        float max = min;
        for (const auto& point : polygon) {
            float proj = kn::math::dot(point,axis);
            if (proj < min) min = proj;
            if (proj > max) max = proj;
        }
        return { min, max };
    }

    inline float overlap(minmax a,minmax b){
        if (a.max < b.min || b.max < a.min) return 0;
        float overlapDepth = std::min(a.max, b.max) - std::max(a.min, b.min);
        return (overlapDepth > 0) ? overlapDepth : 0;
    }

    inline bool SATCollision(const std::vector<kn::math::Vec2>& A,const std::vector<kn::math::Vec2>& B,kn::math::Vec2& mtv){
        float minoverlap = std::numeric_limits<float>::infinity();
        kn::math::Vec2 smallest_axis;

        std::vector<kn::math::Vec2> Axis = getPolygonNormals(A);
        std::vector<kn::math::Vec2> Bxis = getPolygonNormals(B);

        for (const kn::math::Vec2& axis : Bxis) {
            minmax Aproj = project(A, axis);
            minmax Bproj = project(B, axis);

            float o = overlap(Aproj,Bproj);
            if (!o) return false;
            if (o < minoverlap) {
                minoverlap = o;
                smallest_axis = axis;
            }
        }
        for (const kn::math::Vec2& axis : Axis) {
            minmax Aproj = project(A, axis);
            minmax Bproj = project(B, axis);

            float o = overlap(Aproj,Bproj);
            if (!o) return false;
            if (o < minoverlap) {
                minoverlap = o;
                smallest_axis = axis;
            }
        }

        kn::math::Vec2 centerA{0, 0}, centerB{0, 0};
        for (const auto& v : A) centerA = centerA + v;
        for (const auto& v : B) centerB = centerB + v;
        centerA = centerA * (1.0f / A.size());
        centerB = centerB * (1.0f / B.size());

        kn::math::Vec2 direction = centerB - centerA;
        if (kn::math::dot(direction, smallest_axis) < 0)
            smallest_axis = smallest_axis * -1;


        mtv = (smallest_axis*minoverlap);
        return true;

    }
    inline std::vector<kn::math::Vec2> getVertices (const kn::Rect& rect){
        return {{rect.left(),rect.top()},{rect.right(),rect.top()},{rect.right(),rect.bottom()},{rect.left(),rect.bottom()}};
    }

    inline std::vector<std::string> iterateFolder(const std::string& folder){
        fs::path directorypath = folder;

        std::vector<std::string> result;

        if (fs::exists(directorypath)
            && fs::is_directory(directorypath)) {
            for (const auto& entry :
                fs::directory_iterator(directorypath)) {
                result.push_back(entry.path().string());
            }
        }
        else {
            std::cerr << "Directory not found." << std::endl;
        }
        sort(result.begin(),result.end());
        return result;
    }

}//namespace utils
