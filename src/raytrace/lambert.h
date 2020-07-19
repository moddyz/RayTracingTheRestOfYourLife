#pragma once

/// \file raytrace/lambert.h
///
/// Lambert material representation.

#include <gm/types/vec3f.h>

#include <raytrace/hitRecord.h>
#include <raytrace/material.h>
#include <raytrace/randomUnitVector.h>
#include <raytrace/texture.h>

RAYTRACE_NS_OPEN

/// \class Lambert
///
/// The lambert material scatters a ray towards a point within random unit sphere
/// tangent to the hit point. (Improve on this definition?)
///
/// Lambert has an associated color attribute, named "albedo".
class Lambert : public Material
{
public:
    /// Explicit constructor with an albedo texture.
    ///
    /// \param i_albedo The texture associated with the color of this material.
    inline explicit Lambert( const TextureSharedPtr& i_albedo )
        : m_albedo( i_albedo )
    {
    }

    inline virtual bool Scatter( const raytrace::Ray& i_ray,
                                 const HitRecord&     i_hitRecord,
                                 gm::Vec3f&           o_attenuation,
                                 raytrace::Ray&       o_scatteredRay ) const override
    {
        // Produce random scatter direction.
        gm::Vec3f rayTarget = i_hitRecord.m_position + // From the hit point...
                              i_hitRecord.m_normal +   // Add a unit in the direction of the normal.
                              RandomUnitVector();      // Add random unit vector.
        o_scatteredRay = raytrace::Ray( /* origin */ i_hitRecord.m_position,
                                        /* direction */ gm::Normalize( rayTarget - i_hitRecord.m_position ),
                                        /* time */ i_ray.Time() );

        // Sample albedo texture.
        o_attenuation = m_albedo->Sample( i_hitRecord.m_uv, i_hitRecord.m_position );

        return true;
    }

private:
    TextureSharedPtr m_albedo;
};

RAYTRACE_NS_CLOSE
