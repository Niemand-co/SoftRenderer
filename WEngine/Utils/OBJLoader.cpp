#include "OBJLoader.h"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Math/Vector.h"
#include "Render/Vertex.h"

Mesh* OBJLoader::Load(char* filePath)
{
	std::ifstream obj(filePath);
	std::string line;
	std::vector<Vertex> vertices;
	std::vector<Vec3> verts;
	std::vector<Vec3> normals;
	std::vector<Vec2> uvs;
	std::vector<uint32_t> indices;
	while (std::getline(obj, line))
	{
		if (line.substr(0, 2) == "vt")
		{
			std::istringstream in(line.substr(3));
			float u, v;
			in>>u;
			in>>v;
			uvs.emplace_back(u, v);
		}
		else if (line.substr(0, 2) == "vn")
		{
			std::istringstream in(line.substr(3));
			float x, y, z;
			in>>x;
			in>>y;
			in>>z;
			normals.emplace_back(x, y, z);
		}
		else if (line.substr(0, 1) == "v")
		{
			std::istringstream in(line.substr(2));
			float x, y, z;
			in>>x;
			in>>y;
			in>>z;
			verts.emplace_back(x, y, z);
		}
		else if (line.substr(0, 1) == "f")
		{
			std::istringstream in(line.substr(2));
			int offset = vertices.size();
			for (int i = 0; i < 3; ++i)
			{
				std::string str;
				std::vector<int> index;
				index.reserve(3);
				in>>str;

				for (int l = 0, r = 1; r < str.size(); ++r)
				{
					if (str[r] == '/')
					{
						index.push_back(atoi(str.substr(l, r).c_str()));
						l = r + 1;
					}
					if (r == str.size() - 1)
					{
						index.push_back(atoi(str.substr(l, int(long long(r) + 1)).c_str()));
						break;
					}
				}
				indices.push_back(offset + i);
				Vertex vert;
				vert.position = verts[int(long long(index[0]) - 1)];
				vert.uv = uvs[int(long long(index[1]) - 1)];
				vert.normal = normals[int(long long(index[2]) - 1)];
				vert.color = Vec3(0.5f, 0.0f, 0.0f);
				vertices.emplace_back(vert);
			}
		}
		else if (line.substr(0, 1) == "#")
		{

		}
	}
	Mesh* mesh = new Mesh();
	mesh->AddVertices(&vertices[0], vertices.size());
	mesh->AddIndices(&indices[0], indices.size());
	return mesh;
}