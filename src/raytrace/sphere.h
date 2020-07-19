#pragma once

/// \file raytrace/sphere.h
///
/// Representation of a ray-traceable sphere.

#include <raytrace/attribute.h>
#include <raytrace/ray.h>
#include <raytrace/sceneObject.h>

#include <gm/base/constants.h>

#include <gm/functions/contains.h>
#include <gm/functions/expand.h>
#include <gm/functions/normalize.h>
#include <gm/functions/rayPosition.h>
#include <gm/functions/raySphereIntersection.h>

RAYTRACE_NS_OPEN

/// \class Sphere
///
/// Sphere is a 3D geometric surface described by a \em origin and \em radius, such that
/// the distance between all surface points and the origin is its radius.
class Sphere : public SceneObject
{
public:
    /// Construct a static Sphere with a origin and radius.
    ///
    /// \param i_origin The origin of the sphere.
    /// \param i_radius The radius of the sphere.
    /// \param i_material Optional material assigned to the sphere.
    inline explicit Sphere( const gm::Vec3f& i_origin, float i_radius, MaterialSharedPtr i_material = nullptr )
        : m_origin( {{0, i_origin}} )
        , m_radius( i_radius )
        , m_material( i_material )
    {
    }

    /// Construct a dynamic (moving!) Sphere with a origin and radius.
    ///
    /// \param i_origin The origin of the sphere.
    /// \param i_radius The radius of the sphere.
    /// \param i_material Optional material assigned to the sphere.
    inline explicit Sphere( const Attribute< gm::Vec3f >& i_origin,
                            float                         i_radius,
                            MaterialSharedPtr             i_material = nullptr )
        : m_origin( i_origin )
        , m_radius( i_radius )
        , m_material( i_material )
    {
    }

    virtual inline bool
    Hit( const raytrace::Ray& i_ray, const gm::FloatRange& i_magnitudeRange, HitRecord& o_record ) const override
    {
        gm::FloatRange intersections;
        if ( gm::RaySphereIntersection( m_origin.Value( i_ray.Time() ),
                                        m_radius,
                                        i_ray.Origin(),
                                        i_ray.Direction(),
                                        intersections ) > 0 )
        {
            if ( gm::Contains( i_magnitudeRange, intersections.Min() ) )
            {
                _RecordHit( i_ray, intersections.Min(), o_record );
                return true;
            }
            else if ( gm::Contains( i_magnitudeRange, intersections.Max() ) )
            {
                _RecordHit( i_ray, intersections.Max(), o_record );
                return true;
            }
        }

        // Sorry, missed!
        return false;
    }

    virtual inline gm::Vec3fRange Extent( const std::vector< float >& i_times ) const override
    {
        gm::Vec3fRange extent;
        for ( float time : i_times )
        {
            // Sample values at time.
            gm::Vec3f origin = m_origin.Value( time );
            gm::Vec3f hypotenuse( m_radius, m_radius, m_radius );

            // Compute extent for the current time sample.
            gm::Vec3fRange extentSample(
                /* min */ origin - hypotenuse,
                /* max */ origin + hypotenuse );

            // Expand range extent.
            extent = gm::Expand( extent, extentSample );
        }

        return extent;
    }

private:
    /// Helper method to record a ray hitting the sphere.
    ///
    /// \param i_ray The ray.
    /// \param i_rayMagnitude the magnitude of the ray intersection.
    /// \param o_record the record of a ray hit.
    inline void _RecordHit( const raytrace::Ray& i_ray, float i_rayMagnitude, HitRecord& o_record ) const
    {
        o_record.m_position  = gm::RayPosition( i_ray.Origin(), i_ray.Direction(), i_rayMagnitude );
        o_record.m_normal    = ( o_record.m_position - m_origin.Value( i_ray.Time() ) ) / m_radius;
        o_record.m_uv        = _ComputeUV( o_record.m_normal );
        o_record.m_magnitude = i_rayMagnitude;
        o_record.m_material  = m_material;
    }

    /// Helper method to compute the normalised UV coordinates for a sphere, given the surface normal.
    inline gm::Vec2f _ComputeUV( const gm::Vec3f& i_normal ) const
    {
        // atan2 returns a value inclusive of the range (-pi, pi)
        float phi = atan2( i_normal.Z(), i_normal.X() );

        // asin returns a value inclusive of the range (-pi/2, pi/2)
        float theta = asin( i_normal.Y() );

        // The normalised coordinate "u" can be computed for the latitude angle (phi)
        // around the pole of a sphere:
        //
        // u = phi / 2*PI
        //
        // XXX: Why are we subtracting the result from 1.0f?
        float u = 1.0f - ( ( phi + GM_PI ) / ( 2.0f * GM_PI ) );

        // The normalised coordinate "v" can be computed for the longitude angle (theta) down
        // from the pole of the sphere:
        //
        // v = theta / PI
        float v = ( theta + ( GM_PI / 2.0f ) ) / GM_PI;

        return gm::Vec2f( u, v );
    }

    // The origin of the sphere.
    Attribute< gm::Vec3f > m_origin;

    // The radius of the sphere.
    float m_radius = 0.0f;

    // Assigned material.
    MaterialSharedPtr m_material;
};

RAYTRACE_NS_CLOSE
