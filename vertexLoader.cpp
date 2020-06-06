#include<vector>
#include<fstream>
#include<boost/algorithm/string.hpp>
#include<iostream>

struct float3 {
    float3(float _x = 0, float _y = 0, float _z = 0) : 
        x(_x), y(_y),z(_z) {};
    float x;
    float y;
    float z;
};

struct float4 {
    float4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) : 
        x(_x), y(_y),z(_z), w(_w) {};
    float x;
    float y;
    float z;
    float w;
};

struct Vertex {
    float3 v1;
    float4  color;
};

static bool isSpace(char c) {
    return c == ' ';
};

static std::vector<std::string> loadFileToString(std::string fromFile) {

    std::vector<std::string> contents;
    int filelength = 0;

    std::ifstream infile;
    infile.open(fromFile);

    while(!infile.eof()) {
        std::string tsrc = "";
        std::getline(infile, tsrc);
        contents.push_back(tsrc);
        ++filelength;
    }
    infile.close();

    return contents;
}

static std::vector<Vertex> loadTriangles(std::string fromFile) {
    std::vector<std::string> text_raw = loadFileToString(fromFile);
    std::vector<Vertex> vertices = std::vector<Vertex>();

    //vertex being built
    float3 v0 = float3();
    float4 v1 = float4();
    Vertex v = Vertex();
    v.color = v1;
    v.v1 = v0;

    for(int i=0; i < text_raw.size(); ++i) {
        std::string raw_line = text_raw[i];

            std::vector<std::string> s_floats = std::vector<std::string>();
            std::vector<float> floats = std::vector<float>();
           
            boost::split(s_floats, raw_line, isSpace);
            for(int j=0; j<s_floats.size(); ++j) {
                floats.push_back(std::stof(s_floats[j]));
            }
            v.v1 = float3(floats[0], floats[1], floats[2]);
            v.color = float4(floats[3], floats[4], floats[5], floats[6]);
            vertices.push_back(v);

            for(int i=0; i<vertices.size(); ++i) {
            //    std::cout << v.v1.x << v.v1.y << v.v1.z << v.color.x << v.color.y << v.color.z << v.color.w << std::endl;
            }
    }

    for(int i=0; i<vertices.size(); ++i) {
     //   std::cout << vertices[i].v1.x << vertices[i].v1.y << vertices[i].v1.z << vertices[i].color.x << vertices[i].color.y << vertices[i].color.z << vertices[i].color.w << std::endl;
    }
    
    return vertices;
}