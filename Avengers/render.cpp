#include "pch.h"
#include "Render.h"
#include "Avengers.h"

void init_graphics_stub()
{
	Avengers* hud = Avengers::get_instance();
	if (hud && hud->inst_render)
		hud->inst_render->init_graphics();
}

void __cdecl EngineDraw_Hook()
{
	Avengers* hud = Avengers::get_instance();
	if (hud && hud->inst_hooks && hud->inst_render)
	{
		hud->inst_hooks->hook_map["EngineDraw"]->original(EngineDraw_Hook)();
		hud->inst_render->enginedraw();
	}
}

HRESULT __stdcall EndScene_Hook(LPDIRECT3DDEVICE9 dev)
{
	Avengers* hud = Avengers::get_instance();
	if (hud && hud->inst_hooks && hud->inst_render)
	{
		auto orig = hud->inst_hooks->hook_map["EndScene"]->original(EndScene_Hook)(dev);
		hud->inst_render->endscene(dev);
		return orig;
	}
	return 1;
}

HRESULT __stdcall Reset_Hook(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{

	Avengers* hud = Avengers::get_instance();
	if (hud && hud->inst_hooks && hud->inst_render)
	{

		auto orig = hud->inst_hooks->hook_map["Reset"]->original(Reset_Hook);
		hud->inst_render->invalidate_objects(pDevice);
		HRESULT rval = orig(pDevice, pPresentationParameters);
		hud->inst_render->create_objects(pDevice);
		return rval;
	}
	return 1;
}
void imgui_easy_theming(ImVec4 color_for_text, ImVec4 color_for_head, ImVec4 color_for_area, ImVec4 color_for_body, ImVec4 color_for_pops)
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.58f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.95f);
	//style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.58f);
	style.Colors[ImGuiCol_Border] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.47f);

	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	//style.Colors[ImGuiCol_ComboBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);

	style.Colors[ImGuiCol_CheckMark] = ImColor(158, 151, 169, 255).Value;
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.50f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.50f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_Tab] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.76f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.86f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	//	style.Colors[ImGuiCol_Column] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.32f);
	//	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	//	style.Colors[ImGuiCol_ColumnActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.15f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	//	style.Colors[ImGuiCol_CloseButton] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.16f);
	//	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.39f);
	//	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImColor(130, 174, 51, 255).Value;// ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.43f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(color_for_pops.x, color_for_pops.y, color_for_pops.z, 0.92f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImColor(0, 0, 0, 150).Value;
}


void SetupImGuiStyle2()
{
	static ImVec4 color_for_text = ImVec4(.92f, .94f, .94f, 0);
	static ImVec4 color_for_head = ImVec4(ImColor(65, 60, 73, 255).Value);
	static ImVec4 color_for_area = ImVec4(ImColor(82, 75, 92, 255).Value);
	static ImVec4 color_for_body = ImVec4(ImColor(0, 0, 0, 255).Value);
	static ImVec4 color_for_pops = ImColor(40, 37, 45, 255).Value;

	ImGui::GetStyle().WindowRounding = 0.0f;
	ImGui::GetStyle().ChildRounding = 0.0f;
	ImGui::GetStyle().FrameRounding = 0.0f;
	ImGui::GetStyle().GrabRounding = 0.0f;
	ImGui::GetStyle().PopupRounding = 0.0f;
	ImGui::GetStyle().ScrollbarRounding = 0.0f;
	ImGui::GetStyle().FramePadding = ImVec2(2, 2);
	ImGui::GetStyle().WindowPadding = ImVec2(5, 5);
	ImGui::GetStyle().ItemInnerSpacing = ImVec2(15, 0);
	ImGui::GetStyle().AntiAliasedFill = true;
	ImGui::GetStyle().AntiAliasedLines = true;
	

	static bool first_run = true;
	if (first_run)
	{
		imgui_easy_theming(color_for_text, color_for_head, color_for_area, color_for_body, color_for_pops);
		first_run = false;
	}

}

void render::init_imgui(LPDIRECT3DDEVICE9 dev)
{
	if (!imgui_initialized)
	{
		Avengers* hud = Avengers::get_instance();
		
		ImGui_ImplDX9_InvalidateDeviceObjects();
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDrawCursor = false;
		ImGui_ImplWin32_Init(Avengers::get_instance()->inst_game->get_window());
		ImGui_ImplDX9_Init(dev);

		hud->toxic_font = io.Fonts->AddFontFromMemoryTTF((void*)(_acbahnschrift), sizeof(_acbahnschrift) - 1, 24.f);
		hud->sep_font = io.Fonts->AddFontFromMemoryTTF((void*)(_acawesomefont1), sizeof(_acawesomefont1) - 1, 24.f);
		
		ImGui_ImplDX9_CreateDeviceObjects();
		imgui_initialized = true;

		SetupImGuiStyle2();
	}
	dev->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFF);
}

void __cdecl render::enginedraw()
{
	Avengers* hud = Avengers::get_instance();

	if(hud->inst_game->is_connected() && hud->inst_ui_menu->lines_toggle)
	{
		hud->inst_ui_90_lines->render();
	}
}

void render::endscene(LPDIRECT3DDEVICE9 dev)
{
	init_imgui(dev);
	auto& io = ImGui::GetIO();

	Avengers* hud = Avengers::get_instance();
	if (hud->want_input)
		io.MouseDrawCursor = true;
	else
		io.MouseDrawCursor = false;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	for (auto& fn : callbacks_render)
		fn();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void render::add_callback(RenderCallback render)
{
	callbacks_render.push_back(render);
}

void render::invalidate_objects(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
}
void render::create_objects(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui_ImplDX9_CreateDeviceObjects();
}
void render::init_graphics()
{
	Avengers* hud = Avengers::get_instance();
	//call the original function first
	hud->inst_hooks->hook_map["InitGraphics"]->original(init_graphics_stub)();
	static LPDIRECT3DDEVICE9 current_device = nullptr;
	if (current_device != hud->inst_game->get_device())
	{
		if (current_device)
		{
			D3DPRESENT_PARAMETERS p;
			current_device->Reset(&p);
		}
		Avengers* hud = Avengers::get_instance();

		if (hud && hud->inst_hooks) //remove the old hooks
		{
			if (hud->inst_hooks->hook_map.find("EndScene") != hud->inst_hooks->hook_map.end())
				hud->inst_hooks->hook_map["EndScene"]->remove();
			if (hud->inst_hooks->hook_map.find("Reset") != hud->inst_hooks->hook_map.end())
				hud->inst_hooks->hook_map["Reset"]->remove();
			if (hud->inst_hooks->hook_map.find("EngineDraw") != hud->inst_hooks->hook_map.end())
				hud->inst_hooks->hook_map["EngineDraw"]->remove();
		}

		current_device = hud->inst_game->get_device();
		uint32_t* g_methodsTable = (uint32_t*)::calloc(119, sizeof(uint32_t));
		if (g_methodsTable)
		{
			imgui_initialized = false;
			::memcpy(g_methodsTable, *(uint32_t**)(hud->inst_game->get_device()), 119 * sizeof(uint32_t));
			hud->inst_hooks->Add("EndScene", g_methodsTable[42], EndScene_Hook, hook_type_detour);
			hud->inst_hooks->Add("Reset", g_methodsTable[16], Reset_Hook, hook_type_detour);
			mem::mem_set(0x6496d8, 0x90, 3); //disable check for developer to engine draw
			hud->inst_hooks->Add("EngineDraw", addr_engine_draw, EngineDraw_Hook, hook_type_detour);
			//update the wndproc hook on init
			hud->inst_input->update_wndproc(hud->inst_game->get_window());
		}
	}
}



render::render(Avengers* hud)
{
	//doing it this way only works if its loaded before initgraphics is called
	hud->inst_hooks->Add("InitGraphics", 0x5f4f09, init_graphics_stub, hook_type_replace_call);
}

render::~render() //hooks are removed when the hook wrapper is destroyed
{
	Avengers* hud = Avengers::get_instance();
	if (hud && hud->inst_hooks)
	{
		if (hud->inst_hooks->hook_map.count("InitGraphics") > 0)
			hud->inst_hooks->hook_map["InitGraphics"]->remove(); //remove hook here in case of a race condition on destructors
		if (hud->inst_hooks->hook_map.count("EndScene") > 0)
			hud->inst_hooks->hook_map["EndScene"]->remove(); //remove hook here in case of a race condition on destructors
		if (hud->inst_hooks->hook_map.count("Reset") > 0)
			hud->inst_hooks->hook_map["Reset"]->remove(); //remove hook here in case of a race condition on destructors
		if (hud->inst_hooks->hook_map.count("EngineDraw") > 0)
			hud->inst_hooks->hook_map["EngineDraw"]->remove(); //remove hook here in case of a race condition on destructors

	}
	ImGui::DestroyContext();
}