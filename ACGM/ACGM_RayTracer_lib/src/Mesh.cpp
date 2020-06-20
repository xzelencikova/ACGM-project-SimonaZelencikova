#include <ACGM_RayTracer_lib/Mesh.h>


//! Mesh constructor
acgm::Mesh::Mesh(const std::string file_name, const glm::mat4 transform, const std::string name, const bool smooth_normal):
    file_name_(file_name), transform_(transform), Model(name), smooth_normal_(smooth_normal)
{
    //! Mesh import and transformation
	mesh_.Import(file_name_);
	mesh_.points->Transform(transform_);
}

//! Calculate intersection between mesh and ray
std::optional<acgm::HitResult> acgm::Mesh::Intersect(std::shared_ptr<acgm::Ray>& ray) const
{
    std::optional<HitResult> min_hit;
    min_hit->ray_param = INFINITY;
    int32_t j;

    //! Find nearest intersection among all triangles
 #pragma omp parallel for private(j)
    for (j = 0; j < mesh_.faces->GetFaceCount(); j++)
    {
        //! Set indexes of the triangle vertexes and construct triangle
        glm::uint vertX = mesh_.faces->GetFaces()[j].x;
        glm::uint vertY = mesh_.faces->GetFaces()[j].y;
        glm::uint vertZ = mesh_.faces->GetFaces()[j].z;
        Triangle triangle = Triangle(mesh_.points->GetPositions()[vertX], mesh_.points->GetPositions()[vertY], mesh_.points->GetPositions()[vertZ]);
        
        //! Call intersection for each triangle
        std::optional<acgm::HitResult> hit = triangle.Intersect(ray);

        if (hit->ray_param > 0.0f && hit->ray_param < min_hit->ray_param)
        {
            glm::vec3 normal_x = mesh_.points->GetNormals()[vertX];
            glm::vec3 normal_y = mesh_.points->GetNormals()[vertY];
            glm::vec3 normal_z = mesh_.points->GetNormals()[vertZ];

            min_hit->ray_param = hit->ray_param;

            if (!smooth_normal_)
                min_hit->normal = glm::normalize(glm::cross(triangle.GetVertexY() - triangle.GetVertexX(), triangle.GetVertexZ() - triangle.GetVertexX()));
            else min_hit->normal = glm::normalize((1- hit->uv.x - hit->uv.y) * normal_x + hit->uv.x * normal_y + hit->uv.y * normal_z);
            min_hit->point = ray->GetPoint(min_hit->ray_param);
        }
    }
    return min_hit;
}
