#pragma once

#include "trianglemesh.h"
#include <glad/glad.h>
#include "aabb.h"

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <memory>

class ObjMesh : public TriangleMesh {
private:
    bool drawAdj;

public:
    static std::unique_ptr<ObjMesh> load(const char* fileName, bool center = false, bool genTangents = false);
    static std::unique_ptr<ObjMesh> loadWithAdjacency(const char* fileName, bool center = false);

    void render() const override;

    const Aabb& getBoundingBox() const { return bbox; }

protected:
    ObjMesh();
    Aabb bbox;  // Bounding Box

    class GlMeshData {
    public:
        std::vector<GLfloat> points;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> texCoords;
        std::vector<GLuint> faces;
        std::vector<GLfloat> tangents;

        void clear() {
            points.clear();
            normals.clear();
            texCoords.clear();
            faces.clear();
            tangents.clear();
        }
        void center(Aabb& bbox);
        void convertFacesToAdjancencyFormat();
    };

    class ObjMeshData {
    public:
        class ObjVertex {
        public:
            int pIdx;
            int nIdx;
            int tcIdx;

            ObjVertex() : pIdx(-1), nIdx(-1), tcIdx(-1) {}
            ObjVertex(std::string& vertString, ObjMeshData* mesh);
            std::string str() {
                return std::to_string(pIdx) + "/" + std::to_string(tcIdx) + "/" + std::to_string(nIdx);
            }
        };

        std::vector<glm::vec3> points;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;
        std::vector<ObjVertex> faces;
        std::vector<glm::vec4> tangents;

        ObjMeshData() {}

        void generateNormalsIfNeeded();
        void generateTangents();
        void load(const char* fileName, Aabb& bbox);
        void toGlMesh(GlMeshData& data);
    };
};
