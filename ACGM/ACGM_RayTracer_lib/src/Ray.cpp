#include <ACGM_RayTracer_lib/Ray.h>


// #TODO Implement your functionality here
acgm::Ray::Ray(glm::vec3 orig, glm::vec3 direct) 
{
	origin = orig;
	direction = direct;
}

glm::vec3 acgm::Ray::GetOrigin() 
{ 
	return origin; 
}

glm::vec3 acgm::Ray::GetDirection() 
{ 
	return direction; 
}

float acgm::Ray::Intersection(std::shared_ptr<acgm::Plane> plane)
{
    glm::vec3 normal = plane->GetPlaneNormal();
    glm::vec3 point = plane->GetPlanePoint();

    float dot2 = glm::dot(normal, direction);

    if (dot2 == 0)
    {
        return -1;
    }

    float t = glm::dot((point - origin), normal) / dot2;

    return t;
}

float acgm::Ray::IntersectionWithTriangle(glm::vec3 &positionX, glm::vec3 &positionY, glm::vec3 &positionZ)
{
    glm::vec3 edge1, edge2, h, s, q;
    float a, f, u, v;

    edge1 = positionY - positionX;
    edge2 = positionZ - positionX;

    h = glm::cross(direction, edge2);
    a = glm::dot(edge1, h);

    if (a == 0)
        return 0;    // This ray is parallel to this triangle.

    f = 1.0 / a;
    s = origin - positionX;
    u = f * glm::dot(s, h);
    if (u <= 0.0 || u > 1.0)
        return 0;
    q = glm::cross(s, edge1);
    v = f * glm::dot(direction, q);
    
    if (v <= 0.0 || u + v > 1.0)
        return 0;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * glm::dot(edge2, q);
    
    return t;
}