#include "CombustibilBar.h"


CombustibilBar::CombustibilBar() {

		{
			combustibilBar = new Mesh("combustibilBar");

			std::vector<VertexFormat> vertices =
			{
				VertexFormat(corner),
				VertexFormat(corner + glm::vec3(75, 0, 0)),
				VertexFormat(corner + glm::vec3(75, 10, 0)),
				VertexFormat(corner + glm::vec3(0, 10, 0)),

			};

			std::vector<unsigned short> indices = {0, 1, 2, 3, 0};
			combustibilBar->SetDrawMode(GL_LINE_LOOP);
			combustibilBar->InitFromData(vertices, indices);
		}

		{
			powerLine = new Mesh("powerLine");

			std::vector<VertexFormat> vertices =
			{
				VertexFormat(corner),
				VertexFormat(corner + glm::vec3(2, 0, 0)),
				VertexFormat(corner + glm::vec3(2, 10, 0)),
				VertexFormat(corner + glm::vec3(0, 10, 0)),
			};

			std::vector<unsigned short> indices = {1, 0, 3, 3, 2, 1};
			powerLine->InitFromData(vertices, indices);
		}

}

CombustibilBar::~CombustibilBar() {
}

Mesh* CombustibilBar::GetCombustibilBar() {
	return combustibilBar;
}

Mesh* CombustibilBar::GetPowerLine() {
	return powerLine;
}