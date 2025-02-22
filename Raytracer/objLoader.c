#include "objLoader.h"
#include "vec3.h"
#include "stdio.h"

#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 64

void pushBack();

int loadOBJ(
	const char * path,
	vec3 **out_vertices, 
	vec3 **out_uvs,
	vec3 **out_normals
){
	printf("Loading OBJ file %s...\n", path);

	//unsigned int *vertexIndices = malloc(BLOCK_SIZE * sizeof(unsigned int));
	//unsigned int *uvIndices = malloc(BLOCK_SIZE * sizeof(unsigned int));
	//unsigned int *normalIndices = malloc(BLOCK_SIZE * sizeof(unsigned int));
	vec3 *temp_vertices = malloc(BLOCK_SIZE * sizeof(vec3));
	vec3 *temp_uvs = malloc(BLOCK_SIZE * sizeof(vec3));
	vec3 *temp_normals = malloc(BLOCK_SIZE * sizeof(vec3));

    int vertCount, allocatedVert;
    int uvsCount, allocatedUvs;
    int normalsCount, allocatedNormals;

    vertCount = allocatedVert = uvsCount = allocatedUvs = normalsCount = allocatedNormals = 0;

	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file !\n");
		getchar();
		return 0;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices[vertCount++] = vertex;
            if(vertCount > allocatedVert)
            {
                allocatedVert += BLOCK_SIZE;
                temp_vertices = realloc(temp_vertices, allocatedVert * sizeof(vec3));
            }
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			vec3 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs[uvsCount++] = uv;
            if(uvsCount > allocatedUvs)
            {
                allocatedUvs += BLOCK_SIZE;
                temp_uvs = realloc(temp_uvs, allocatedUvs * sizeof(vec3));
            }
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals[normalsCount++] = normal;
            if(normalsCount > allocatedNormals)
            {
                allocatedNormals += BLOCK_SIZE;
                temp_normals = realloc(temp_normals, allocatedNormals * sizeof(vec3));
            }
		//}else if ( strcmp( lineHeader, "f" ) == 0 ){
			//std::string vertex1, vertex2, vertex3;
			/*
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (1){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return 0;
			}
            
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
            */
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[100];
			fgets(stupidBuffer, 100, file);
		}

	}
    /*
	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);
		out_normals .push_back(normal);
	
	}
    */
    *out_vertices = temp_vertices;
	*out_uvs = temp_uvs;
	*out_normals = temp_normals;

	fclose(file);
	return 1;
}