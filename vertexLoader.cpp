#include<vector>
#include<fstream>
#include<iostream>
#include<sstream>

struct float3 {
    float3(float _x = 0, float _y = 0, float _z = 0) : 
        x(_x), y(_y),z(_z) {};
    float x;
    float y;
    float z;
};

struct Triangle {
    float3 v1;
    float3 v2;
    float3 v3;
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

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

static std::vector<Triangle> loadTriangles(std::string fromFile) {
    std::vector<std::string> text_raw = loadFileToString(fromFile);
    std::vector<Triangle> triangle_vector = std::vector<Triangle>();

    //triangle being built
    Triangle triangle = Triangle();
    float3 v = float3();
    v.x = 0;
    v.y = 0;
    v.z = 0;
    triangle.v1 = v;
    triangle.v2 = v;
    triangle.v3 = v;

    int vertexToPush = 0;

    for(int i=0; i < text_raw.size(); ++i) {
        std::string raw_line = text_raw[i];
        if(raw_line[0] == '*') {
            //push triangle triangle
            triangle_vector.push_back(triangle);
            std::cout << "a" << std::endl;
            vertexToPush = 0;
        }else {
            std::vector<std::string> s_floats = split(raw_line, ' ');
            std::vector<float> floats = std::vector<float>();

            for(int j=0; j<s_floats.size(); ++j) {
                floats.push_back(std::stof(s_floats[j]));
            }

            if(vertexToPush == 0) {
                float3 f3 = float3(floats[0], floats[1], floats[2]);;
                triangle.v1 = f3;
            }else if(vertexToPush == 1) {
                float3 f3 = float3(floats[0], floats[1], floats[2]);;
                triangle.v2 = f3;
            }else if(vertexToPush == 2) {
                float3 f3 = float3(floats[0], floats[1], floats[2]);;
                triangle.v3 = f3;
            }
            ++vertexToPush;
        }
    }
    
    for(int i=0; i<triangle_vector.size(); ++i) {
        std::cout << triangle_vector[i].v1.x << " " << triangle_vector[i].v1.y << " " << triangle_vector[i].v1.z << std::endl;
        std::cout << triangle_vector[i].v2.x << " " << triangle_vector[i].v2.y << " " << triangle_vector[i].v2.z << std::endl;
        std::cout << triangle_vector[i].v3.x << " " << triangle_vector[i].v3.y << " " << triangle_vector[i].v3.z << std::endl;
    }
    return triangle_vector;
}

/*    
for(int i=0; i<text_raw.size(); ++i) {
        std::string line_raw = text_raw.at(i);

        std::vector<float3> triangle = std::vector<float3>();
        for(int j=0; j<3; ++j) {
            std::vector<float> point = std::vector<float>();
            
            for(int k=0; k<3; ++k) {
                const char* line_raw_c = line_raw.c_str();
                std::vector<std::string> float_strs = std::vector<std::string>();
                std::vector<char> cbuf = std::vector<char>();
                for(int l=0; l<strlen(line_raw_c); ++l) {
                    if(line_raw_c[3*j+l] == ' ') {
                        std::string strbuf = std::string();
                        for(int f=0; f<cbuf.size(); ++f) {
                            strbuf.push_back(cbuf[f]);
                        }
                        float_strs.push_back(strbuf);
                        cbuf = std::vector<char>();
                    }else {
                        cbuf.push_back(line_raw_c[3*j+l]);
                    }
                }

                for(int l=0; l<float_strs.size(); ++l) {
                    point.push_back(std::stof(float_strs[l]));
                }
            }
            float3 ptf3;
            ptf3.x = point[0];
            ptf3.y = point[1];
            ptf3.z = point[2];
            triangle.push_back(ptf3);
        }
        Triangle triangle_t;
        triangle_t.v1 = triangle[0];
        triangle_t.v2 = triangle[1];
        triangle_t.v3 = triangle[2];
        triangle_vector.push_back(triangle_t);
    }

    std::cout << triangle_vector[0].v1.x << ",";
    std::cout << triangle_vector[0].v1.y << ",";
    std::cout << triangle_vector[0].v1.z << std::endl;

    std::cout << triangle_vector[0].v2.x << ",";
    std::cout << triangle_vector[0].v2.y << ",";
    std::cout << triangle_vector[0].v2.z << std::endl;

    std::cout << triangle_vector[0].v3.x << ",";
    std::cout << triangle_vector[0].v3.y << ",";
    std::cout << triangle_vector[0].v3.z << std::endl;
*/