#include "loadOBJ.h"
#include <math.h>

GLuint loadObject(string path) {
	//vertices and normals are used to temporarily store the values, because obj files 
	//give you seperate lists of vertices and normals, but the shader needs them together
	vector<GLfloat> vertices;
	vector<GLfloat> normals;
	vector<GLfloat> actualVertices;

	//read the sourcefile from path and put into sourceFile
	string data;
	ifstream sourceFile(path);

	while (!sourceFile.eof()) {
		//moves the next line from sourceFile to data
		getline(sourceFile, data, '\n');
		//cout << data << '\n';
		if (data[0] == 'v') {
			//no textures in my object loader
			if (data[1] == 't') continue;
			//need this later, because vertices start with 'v' and normals with 'vn'
			bool isNormal = (data[1] == 'n');
			//placeholders for the three numbers after 'v'
			string x, y, z;
			//delete 'v ' or 'vn ' to get to the coordinates
			data.erase(0, data.find(' ') + 1);

			//the coordinates are seperated by spaces
			int nextspace = data.find(' ');
			//copying from data to x until next space
			x.append(data, 0, nextspace);
			//shorten data from the left to and including the next space
			data.erase(0, nextspace + 1);

			nextspace = data.find(' ');
			y.append(data, 0, nextspace);
			data.erase(0, nextspace + 1);

			z.append(data);

			//converting x, y and z to floats and putting them in the right vector
			if (isNormal) {
				normals.push_back(strtof((x).c_str(), 0));
				normals.push_back(strtof((y).c_str(), 0));
				normals.push_back(strtof((z).c_str(), 0));
			}
			else {
				vertices.push_back(strtof((x).c_str(), 0));
				vertices.push_back(strtof((y).c_str(), 0));
				vertices.push_back(strtof((z).c_str(), 0));
			}
		}
		//'f' before the indices, all the vertices and normals come first, so this is okay
		if (data[0] == 'f') {
			//get to the first number
			data.erase(0, 2);
			for (int i = 0; i < 3; i++) {
				/*vertices get repeated in the actual vertex buffer,
				but that's okay because we have a normal for every face anyway.
				obj files have three indices for every vertex; the first is the vertex coordinate,
				the second is texture, the third is normal vector. i don't use textures (yet).
				Color will be set as gray for now*/

				//getting the vertex index and normal index, remembering that obj files start counting
				//at 1 like idiots
				int v = stoi(data) - 1;
				//erase up to next slash
				data.erase(0, data.find('/') + 1);
				//erase up to next slash and delete gay vt index
				data.erase(0, data.find('/') + 1);
				int n = stoi(data) - 1;
				data.erase(0, data.find(' ') + 1);
				actualVertices.push_back(vertices[3 * v]);
				actualVertices.push_back(vertices[3 * v + 1]);
				actualVertices.push_back(vertices[3 * v + 2]);

				actualVertices.push_back(normals[3 * n]);
				actualVertices.push_back(normals[3 * n + 1]);
				actualVertices.push_back(normals[3 * n + 2]);
			}
		}
	}
	//creating the actual vertex buffer object
	GLuint VBO, VAO;
	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//writing all the vertices into the buffer
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * actualVertices.size(),
		&actualVertices[0],
		GL_STATIC_DRAW
	);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(float),
		(void*)0
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(float),
		(void*) (3 * sizeof(float))
	);

	return VAO;
}

GLuint loadObjectNormalized(string path) {
	//vertices and normals are used to temporarily store the values, because obj files 
	//give you seperate lists of vertices and normals, but the shader needs them together
	vector<GLfloat> vertices;
	vector<GLfloat> normals;
	vector<GLfloat> actualVertices;

	//read the sourcefile from path and put into sourceFile
	string data;
	ifstream sourceFile(path);

	while (!sourceFile.eof()) {
		//moves the next line from sourceFile to data
		getline(sourceFile, data, '\n');
		//cout << data << '\n';
		if (data[0] == 'v') {
			//no textures in my object loader
			if (data[1] == 't') continue;
			//need this later, because vertices start with 'v' and normals with 'vn'
			bool isNormal = (data[1] == 'n');
			//placeholders for the three numbers after 'v'
			string x, y, z;
			//delete 'v ' or 'vn ' to get to the coordinates
			data.erase(0, data.find(' ') + 1);

			//the coordinates are seperated by spaces
			int nextspace = data.find(' ');
			//copying from data to x until next space
			x.append(data, 0, nextspace);
			//shorten data from the left to and including the next space
			data.erase(0, nextspace + 1);

			nextspace = data.find(' ');
			y.append(data, 0, nextspace);
			data.erase(0, nextspace + 1);

			z.append(data);

			//converting x, y and z to floats and putting them in the right vector
			if (isNormal) {
				normals.push_back(strtof((x).c_str(), 0));
				normals.push_back(strtof((y).c_str(), 0));
				normals.push_back(strtof((z).c_str(), 0));
			}
			else {
				GLfloat fx = strtof((x).c_str(), 0);
				GLfloat fy = strtof((y).c_str(), 0);
				GLfloat fz = strtof((z).c_str(), 0);
				float l = std::sqrt(fx * fx + fy * fy + fz * fz);
				vertices.push_back(fx / l);
				vertices.push_back(fy / l);
				vertices.push_back(fz / l);
			}
		}
		//'f' before the indices, all the vertices and normals come first, so this is okay
		if (data[0] == 'f') {
			//get to the first number
			data.erase(0, 2);
			for (int i = 0; i < 3; i++) {
				/*vertices get repeated in the actual vertex buffer,
				but that's okay because we have a normal for every face anyway.
				obj files have three indices for every vertex; the first is the vertex coordinate,
				the second is texture, the third is normal vector. i don't use textures (yet).
				Color will be set as gray for now*/

				//getting the vertex index and normal index, remembering that obj files start counting
				//at 1 like idiots
				int v = stoi(data) - 1;
				//erase up to next slash
				data.erase(0, data.find('/') + 1);
				//erase up to next slash and delete gay vt index
				data.erase(0, data.find('/') + 1);
				int n = stoi(data) - 1;
				data.erase(0, data.find(' ') + 1);
				actualVertices.push_back(vertices[3 * v]);
				actualVertices.push_back(vertices[3 * v + 1]);
				actualVertices.push_back(vertices[3 * v + 2]);

				actualVertices.push_back(normals[3 * n]);
				actualVertices.push_back(normals[3 * n + 1]);
				actualVertices.push_back(normals[3 * n + 2]);
			}
		}
	}
	//creating the actual vertex buffer object
	GLuint VBO, VAO;
	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//writing all the vertices into the buffer
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * actualVertices.size(),
		&actualVertices[0],
		GL_STATIC_DRAW
	);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(float),
		(void*)0
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(float),
		(void*)(3 * sizeof(float))
	);

	return VAO;
}

GLuint loadObjectNoNormals(string path) {
	//vertices and normals are used to temporarily store the values, because obj files 
	//give you seperate lists of vertices and normals, but the shader needs them together
	vector<GLfloat> vertices;
	vector<GLfloat> actualVertices;

	//read the sourcefile from path and put into sourceFile
	string data;
	ifstream sourceFile(path);

	while (!sourceFile.eof()) {
		//moves the next line from sourceFile to data
		getline(sourceFile, data, '\n');
		//cout << data << '\n';
		if (data[0] == 'v' && data[1] == ' ') {
			//placeholders for the three numbers after 'v'
			string x, y, z;
			//delete 'v ' or 'vn ' to get to the coordinates
			data.erase(0, data.find(' ') + 1);

			//the coordinates are seperated by spaces
			int nextspace = data.find(' ');
			//copying from data to x until next space
			x.append(data, 0, nextspace);
			//shorten data from the left to and including the next space
			data.erase(0, nextspace + 1);

			nextspace = data.find(' ');
			y.append(data, 0, nextspace);
			data.erase(0, nextspace + 1);

			z.append(data);

			//converting x, y and z to floats and putting them in the right vector
			vertices.push_back(strtof((x).c_str(), 0));
			vertices.push_back(strtof((y).c_str(), 0));
			vertices.push_back(strtof((z).c_str(), 0));
		}
		//'f' before the indices, all the vertices and normals come first, so this is okay
		if (data[0] == 'f') {
			//get to the first number
			data.erase(0, 2);
			for (int i = 0; i < 3; i++) {
				//remember that obj files start counting at 1 like idiots
				int v = stoi(data) - 1;
				data.erase(0, data.find(' ') + 1);
				actualVertices.push_back(vertices[3 * v]);
				actualVertices.push_back(vertices[3 * v + 1]);
				actualVertices.push_back(vertices[3 * v + 2]);
			}
		}
	}
	//creating the actual vertex buffer object
	GLuint VBO, VAO;

	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//writing all the vertices into the buffer
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * actualVertices.size(),
		&actualVertices[0],
		GL_STATIC_DRAW
	);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		(void*)0
	);
	
	return VAO;
}