#pragma once

#include "de2.h"
#include <iostream>
#include <set>
#include "glm/glm.hpp"
#include "util.h"
#include "map_provider.h"

struct earth {};

struct plate_name {
	std::string name;
};

class plate : public mesh {
	size_t resolution_{ 0 };
public:
	plate(std::string plate_path, size_t resolution);
	
	square b;
	std::string plate_path_;
	corner_normals cn;
	std::array<glm::vec3, 4> corners;
};

class earth_plate : public texture_model {
public:
	earth_plate(std::string plate_path, size_t resolution);
	~earth_plate();

	static map_quest<disk_store>& get_provider();
};


class spheroid : public sub_system<renderer_system> {
public:
	spheroid(double semi_axis_a, double semi_axis_c, size_t resolution) : earth_a(semi_axis_a), c(semi_axis_c), resolution_(resolution) {}
	void process(ecs_s::registry& world, renderer_system& renderer);


	corner_normals& get_corner_normals(std::string plate_path);
	std::array<glm::vec3, 4>& get_corners(std::string plate_path);
	size_t resolution_{ 16 };
private:

	std::set<std::string> get_visible_hierarchy(renderer_system& renderer);
	void evaluate_completed_requests(ecs_s::registry& world);
	//using rtype = decltype(std::declval<de2>().load_model_async<model>());
	double earth_a{ .0f }, c{ .0f };
	std::map<std::string, decltype(std::declval<de2>().load_model_async<model>())> requests_made_;
	std::vector<decltype(std::declval<de2>().load_model_async<model>())> vertices;
	//corner normals cache;
	lru_cache<std::string, corner_normals> cn_cache;
	lru_cache<std::string, std::array<glm::vec3, 4>> c_cache;
};

