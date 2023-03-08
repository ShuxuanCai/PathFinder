#include "SCV.h"
#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

AI::AIWorld world;
std::vector<std::unique_ptr<SCV>> scvs;

// Tuning
float wanderJitter = 1.0f;
float wanderRadius = 50.0f;
float wanderDistance = 100.0f;

void GameInit()
{
	for (int i = 0; i < 10; ++i)
	{
		auto& scv = scvs.emplace_back(std::make_unique<SCV>(world));
		scv->Initialize();
		scv->position.x = X::RandomFloat(100.0f, 900.0f);
		scv->position.y = X::RandomFloat(100.0f, 600.0f);
	}
}

void DrawUI()
{
	ImGui::Begin("Steering", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Seek"))
	{
		for (auto& scv : scvs)
		{
			scv->SetSeek(true);
			scv->SetFlee(false);
			scv->SetArrive(false);
			scv->SetWander(false);
		}
	}

	if (ImGui::Button("Flee"))
	{
		for (auto& scv : scvs)
		{
			scv->SetSeek(false);
			scv->SetFlee(true);
			scv->SetArrive(false);
			scv->SetWander(false);
		}
	}

	if (ImGui::Button("Arrive: slow"))
	{
		for (auto& scv : scvs)
		{
			scv->SetSeek(false);
			scv->SetFlee(false);
			scv->SetDecel(AI::ArriveBehavior::Deceleration::slow);
			scv->SetArrive(true);
			scv->SetWander(false);
		}
	}

	if (ImGui::Button("Arrive: normal"))
	{
		for (auto& scv : scvs)
		{
			scv->SetSeek(false);
			scv->SetFlee(false);
			scv->SetDecel(AI::ArriveBehavior::Deceleration::normal);
			scv->SetArrive(true);
			scv->SetWander(false);
		}
	}

	if (ImGui::Button("Arrive: fast"))
	{
		for (auto& scv : scvs)
		{
			scv->SetSeek(false);
			scv->SetFlee(false);
			scv->SetDecel(AI::ArriveBehavior::Deceleration::fast);
			scv->SetArrive(true);
			scv->SetWander(false);
		}
	}

	if (ImGui::CollapsingHeader("Wander Behavior"))
	{
		ImGui::DragFloat("Jitter", &wanderJitter, 0.1f, 1.0f, 10.0f);
		ImGui::DragFloat("Radius", &wanderRadius, 0.1f, 1.0f, 1000.0f);
		ImGui::DragFloat("Distance", &wanderDistance, 0.1f,1.0f, 1000.0f);
	
		if (ImGui::Button("Wander"))
		{
			for (auto& scv : scvs)
			{
				scv->SetSeek(false);
				scv->SetFlee(false);
				scv->SetArrive(false);
				scv->SetWander(true);
			}
		}
	}

	ImGui::End();
}

bool GameLoop(float deltaTime)
{
	/*world.AddObstacle(X::Math::Circle(300.0f, 300.0f, 100.0f));
	world.AddObstacle(X::Math::Circle(700.0f, 100.0f, 50.0f));
	world.AddObstacle(X::Math::Circle(500.0f, 200.0f, 30.0f));
	world.AddObstacle(X::Math::Circle(700.0f, 400.0f, 10.0f));
	world.AddObstacle(X::Math::Circle(1100.0f, 300.0f, 150.0f));
	world.AddObstacle(X::Math::Circle(500.0f, 600.0f, 100.0f));*/

	for (auto& scv : scvs)
	{
		X::DrawScreenCircle(scv->destination, 12.0f, X::Colors::Red);

		if (X::IsMousePressed(X::Mouse::LBUTTON))
		{
			scv->destination.x = (float)X::GetMouseScreenX();
			scv->destination.y = (float)X::GetMouseScreenY();
		}
	}

	for (auto& scv : scvs)
	{
		scv->Update(deltaTime);
		scv->Render();
	}

	DrawUI();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{

}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}