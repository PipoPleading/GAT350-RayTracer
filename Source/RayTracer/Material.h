#pragma once
#include "Ray.h"
#include "Random.h"
#include "Color.h"

class Material
{
public:
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const = 0;// const <make this pure virtual>
	virtual color3_t GetEmissive() const { return { 0, 0, 0 }; }
};

class Lambertian : public Material
{
public:
	Lambertian(const color3_t& albedo) : m_albedo{ albedo } {}
	//<override the parent Scatter() method>
	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override 
	{
		glm::vec3 target = raycastHit.point + raycastHit.normal + randomInUnitSphere();//<raycast hit point + raycast hit normal + random in unit sphere>
		glm::vec3 direction = normalize(target - raycastHit.point);//<create a direction from raycast hit point to the target and normalize it>;

		scattered = { raycastHit.point, direction };//<set scattered ray with raycast hit point as the origin and the new direction>;
		color = m_albedo;//<set color to material albedo>;

		return true;
	}

protected:
	color3_t m_albedo;
};

class Metal : public Material
{
public:
	Metal(const glm::vec3& albedo, float fuzz) : m_albedo{ albedo }, m_fuzz{ fuzz } {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const override;

protected:
	glm::vec3 m_albedo{ 0 };
	float m_fuzz = 0;
};

class Dielectric : public Material
{
public:
	Dielectric(const glm::vec3& albedo, float index) : m_albedo{ albedo }, m_index{ index } {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const override;

protected:
	glm::vec3 m_albedo{ 1 };
	float m_index{ 1 }; // refraction index
};

class Emissive : public Material
{
public:
	Emissive(const color3_t& albedo, float intensity = 1.0f) : m_albedo{albedo}, m_intensity{ intensity } {}
 
	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override { return false; }
	color3_t GetEmissive() const override { return m_albedo * m_intensity; }
 
private:
	glm::vec3 m_albedo{ 1, 1, 1 };
	float m_intensity{ 1 };
};