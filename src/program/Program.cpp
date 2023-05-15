#include "Program.h"

#include "src/core/Application.h"
#include "src/media/Rendering.h"
#include "src/media/Audio.h"
#include "src/core/Input.h"
#include "src/core/Window.h"
#include "src/core/Logging.h"

void Program::Init()
{
	BodoniModa = CreateFont("game\\BodoniModa.ttf", 99, "BodoniModa");

	images["BillClinton"] = Render_CreateTexture("files\\Bill_Clinton.png");
	images["BillClintonSad"] = Render_CreateTexture("files\\Bill_Clinton_Sad.png");
	images["HillaryClinton"] = Render_CreateTexture("files\\Hillary_Clinton.png");
	images["MainMenu"] = Render_CreateTexture("files\\main_menu.png");
	images["MainMenuOverlay"] = Render_CreateTexture("files\\main_menu_overlay.png");
	images["WhiteHouse"] = Render_CreateTexture("files\\White-House.png");
	images["Textbox"] = Render_CreateTexture("files\\textbox.png");

	audios["HomesAndGardens"] = Mixer_CreateMusic("files\\HomesAndGardens.mp3");
	audios["BillMenuMusic"] = Mixer_CreateMusic("files\\BillMenuMusic.mp3");

	texts["Text_Play"] = Render_CreateTexture_Text("Play", BodoniModa, { MFontParameters::Font_UTF,
		MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Quit"] = Render_CreateTexture_Text("Quit", BodoniModa, { MFontParameters::Font_UTF,
		MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_BillsAffair"] = Render_CreateTexture_Text("Bill's Affair", BodoniModa, { MFontParameters::Font_UTF,
		MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_VersionNum"] = Render_CreateTexture_Text("1.997", BodoniModa, { MFontParameters::Font_UTF,
		MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_You"] = Render_CreateTexture_Text("You", BodoniModa, { MFontParameters::Font_UTF,
		MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Bill"] = Render_CreateTexture_Text("Bill", BodoniModa, { MFontParameters::Font_UTF,
		MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Dialogue1"] = Render_CreateTexture_Text(
		"I hold a great love for the man in this white house, in this year, 1995.", 
		BodoniModa, { MFontParameters::Font_UTF, MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Dialogue2"] = Render_CreateTexture_Text(
		"I see him coming! Oh, God!",
		BodoniModa, { MFontParameters::Font_UTF, MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Dialogue3"] = Render_CreateTexture_Text(
		"Hello there, fine lady. Would you like to have an affair?",
		BodoniModa, { MFontParameters::Font_UTF, MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_ChoiceDialogue"] = Render_CreateTexture_Text(
		"Oh, my God! What do I do?",
		BodoniModa, { MFontParameters::Font_UTF, MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Choice1"] = Render_CreateTexture_Text(
		"Consummate him.",
		BodoniModa, { MFontParameters::Font_UTF, MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Choice2"] = Render_CreateTexture_Text(
		"Run away.",
		BodoniModa, { MFontParameters::Font_UTF, MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Dialogue4"] = Render_CreateTexture_Text(
		"We had a sweet and loving night, and he was later impeached. I killed myself over the grief.",
		BodoniModa, { MFontParameters::Font_UTF, MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Dialogue5"] = Render_CreateTexture_Text(
		"There is no exit. He will have you.",
		BodoniModa, { MFontParameters::Font_UTF, MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Choices"] = Render_CreateTexture_Text(
		"Yes.\nNo.",
		BodoniModa, { MFontParameters::Font_UTF, MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Dialogue999"] = Render_CreateTexture_Text(
		"There is an illusion of choice.\nThere is no exit. He will have you.",
		BodoniModa, { MFontParameters::Font_UTF, MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });
	texts["Text_Dialogue-1"] = Render_CreateTexture_Text(
		"Bill's current location is unknown.",
		BodoniModa, { MFontParameters::Font_UTF, MFontParameters::Font_Solid, { 255, 255, 255, 255 }, { 0, 0, 0, 255 }, 0 });

	for (auto& m : images)
		Render_LoadTexture(m.second);
	for (auto& m : texts)
		Render_LoadTexture(m.second);

	state = 0;
	state_event = false;
}

void Program::OnUpdate()
{
	if (GetKeyDown(SDL_SCANCODE_ESCAPE) == true)
	{
		App_Quit();
	}

	if (cooldown > 0)
		cooldown -= 1;

	switch (state)
	{
	case 0:
		if (GetMouseButtonPressed(Mouse_LeftButton)) // Play Button.
		{
			int x1 = (65);
			int x2 = (int)(65 + (texts["Text_Play"]->width * 0.6));
			int y1 = (int)((Window_GetHeight() / 3) + ((texts["Text_Play"]->height / 2)) - 35);
			int y2 = (int)((Window_GetHeight() / 3) + ((texts["Text_Play"]->height / 2)) + 35);
			if (x1 < GetMouseX() and GetMouseX() < x2)
			{
				if (y1 < GetMouseY() and GetMouseY() < y2)
				{
					state_event = false;
					state = 1;
					break;
				}
			}

			cooldown = cooldown_max;
		}
		if (GetMouseButtonPressed(Mouse_LeftButton)) // Quit Button.
		{
			int x1 = (65);
			int x2 = (int)(65 + (texts["Text_Play"]->width * 0.6));
			int y1 = (int)((Window_GetHeight() / 3) + ((texts["Text_Play"]->height / 2)) + ((texts["Text_Quit"]->height / 2)) - 35);
			int y2 = (int)((Window_GetHeight() / 3) + ((texts["Text_Play"]->height / 2)) + ((texts["Text_Quit"]->height / 2)) + 35);
			if (x1 < GetMouseX() and GetMouseX() < x2)
			{
				if (y1 < GetMouseY() and GetMouseY() < y2)
				{
					App_Quit();
				}
			}
		}

		if (state_event == false)
		{
			Mixer_PlayMusic(audios["BillMenuMusic"], M_MIXER_INFINITE_LOOP);

			state_event = true;
		}

		PreRenderState();

		// Draw Main Menu background.
		Render_DrawQuad_Texture( { (int)(images["MainMenu"]->width / 2), (int)(images["MainMenu"]->height / 2) }, 
			{ (images["MainMenu"]->width), (images["MainMenu"]->height) }, 
			images["MainMenu"]);
		// Draw Main Menu overlay.
		Render_DrawQuad_Texture({ (int)(images["MainMenuOverlay"]->width / 2), (int)(images["MainMenuOverlay"]->height / 2) },
			{ (images["MainMenuOverlay"]->width), (images["MainMenuOverlay"]->height) },
			images["MainMenuOverlay"]);

		// Draw title text.
		Render_DrawQuad_Texture({ (int)(Window_GetWidth() - (texts["Text_BillsAffair"]->width / 2)), 
			(int)(Window_GetHeight() - ((texts["Text_BillsAffair"]->height / 2)) - (unsigned int)(texts["Text_VersionNum"]->height * 0.5)) },
			{ (unsigned int)(texts["Text_BillsAffair"]->width * 0.8), (unsigned int)(texts["Text_BillsAffair"]->height * 0.8) },
			texts["Text_BillsAffair"]);
		// Draw version text.
		Render_DrawQuad_Texture({ (int)(Window_GetWidth() - (texts["Text_VersionNum"]->width / 2)),
			(int)(Window_GetHeight() - ((texts["Text_VersionNum"]->height / 2))) },
			{ (unsigned int)(texts["Text_VersionNum"]->width * 0.5), (unsigned int)(texts["Text_VersionNum"]->height * 0.5) },
			texts["Text_VersionNum"]);

		// Draw play button.
		Render_DrawQuad_Texture({ (int)(25 + (texts["Text_Play"]->width / 2)),
			(int)((Window_GetHeight() / 3) + ((texts["Text_Play"]->height / 2)))},
			{ (unsigned int)(texts["Text_Play"]->width * 0.35), (unsigned int)(texts["Text_Play"]->height * 0.35) },
			texts["Text_Play"]);
		// Draw quit button.
		Render_DrawQuad_Texture({ (int)(25 + (texts["Text_Quit"]->width / 2)),
			(int)((Window_GetHeight() / 3) + (unsigned int)(texts["Text_Play"]->width * 0.5) + ((texts["Text_Quit"]->height / 2))) },
			{ (unsigned int)(texts["Text_Quit"]->width * 0.35), (unsigned int)(texts["Text_Quit"]->height * 0.35) },
			texts["Text_Quit"]);

		RenderState();
		
		break;

	case 1:
		if (state_event == false)
		{
			Mixer_StopMusic();
			Mixer_PlayMusic(audios["HomesAndGardens"], M_MIXER_INFINITE_LOOP);

			state_event = true;
		}

		if (GetMouseButtonPressed(Mouse_LeftButton) and cooldown == 0) // Next.
		{
			state_event = false;
			state = 2;
			cooldown = cooldown_max;
			break;
		}

		PreRenderState();

		Render_DrawQuad_Texture({ (int)(images["WhiteHouse"]->width / 2), (int)(images["WhiteHouse"]->height / 2) },
			{ (images["WhiteHouse"]->width), (images["WhiteHouse"]->height) },
			images["WhiteHouse"]);



		Render_DrawQuad_Texture({ (int)(images["Textbox"]->width / 2), (int)((images["Textbox"]->height / 2) +
									Window_GetHeight() - (images["Textbox"]->height)) },
			{ (images["Textbox"]->width), (images["Textbox"]->height) },
			images["Textbox"]);
		Render_DrawQuad_Texture({ (int)(195), 
			(int)(Window_GetHeight() - (images["Textbox"]->height) + 50) },
			{ (unsigned int)(texts["Text_Dialogue1"]->width * 0.3), (unsigned int)(texts["Text_Dialogue1"]->height * 0.3) },
			texts["Text_Dialogue1"], true);
		Render_DrawQuad_Texture({ (int)(235 + (texts["Text_You"]->width / 2)), (int)((texts["Text_You"]->height / 2) +
									Window_GetHeight() - (images["Textbox"]->height) - 45) },
			{ (unsigned int)(texts["Text_You"]->width * 0.4), (unsigned int)(texts["Text_You"]->height * 0.4) },
			texts["Text_You"]);

		RenderState();

		break;

	case 2:
		if (GetMouseButtonPressed(Mouse_LeftButton) and cooldown == 0) // Next.
		{
			state_event = false;
			state = 3;
			cooldown = cooldown_max;
			break;
		}

		PreRenderState();

		Render_DrawQuad_Texture({ (int)(images["WhiteHouse"]->width / 2), (int)(images["WhiteHouse"]->height / 2) },
			{ (images["WhiteHouse"]->width), (images["WhiteHouse"]->height) },
			images["WhiteHouse"]);



		Render_DrawQuad_Texture({ (int)(images["Textbox"]->width / 2), (int)((images["Textbox"]->height / 2) +
									Window_GetHeight() - (images["Textbox"]->height)) },
			{ (images["Textbox"]->width), (images["Textbox"]->height) },
			images["Textbox"]);
		Render_DrawQuad_Texture({ (int)(195),
			(int)(Window_GetHeight() - (images["Textbox"]->height) + 50) },
			{ (unsigned int)(texts["Text_Dialogue2"]->width * 0.3), (unsigned int)(texts["Text_Dialogue2"]->height * 0.3) },
			texts["Text_Dialogue2"], true);
		Render_DrawQuad_Texture({ (int)(235 + (texts["Text_You"]->width / 2)), (int)((texts["Text_You"]->height / 2) +
									Window_GetHeight() - (images["Textbox"]->height) - 45) },
			{ (unsigned int)(texts["Text_You"]->width * 0.4), (unsigned int)(texts["Text_You"]->height * 0.4) },
			texts["Text_You"]);

		RenderState();

		break;

	case 3:
		if (GetMouseButtonPressed(Mouse_LeftButton) and cooldown == 0) // Next.
		{
			state_event = false;
			state = 4;
			cooldown = cooldown_max;
			break;
		}

		PreRenderState();

		Render_DrawQuad_Texture({ (int)(images["WhiteHouse"]->width / 2), (int)(images["WhiteHouse"]->height / 2) },
			{ (images["WhiteHouse"]->width), (images["WhiteHouse"]->height) },
			images["WhiteHouse"]);

		Render_DrawQuad_Texture({ (int)(Window_GetWidth() / 2), (int)(Window_GetHeight() - (images["BillClinton"]->height / 2)) },
			{ (images["BillClinton"]->width), (images["BillClinton"]->height) },
			images["BillClinton"]);

		Render_DrawQuad_Texture({ (int)(images["Textbox"]->width / 2), (int)((images["Textbox"]->height / 2) +
									Window_GetHeight() - (images["Textbox"]->height)) },
			{ (images["Textbox"]->width), (images["Textbox"]->height) },
			images["Textbox"]);
		Render_DrawQuad_Texture({ (int)(195),
			(int)(Window_GetHeight() - (images["Textbox"]->height) + 50) },
			{ (unsigned int)(texts["Text_Dialogue3"]->width * 0.3), (unsigned int)(texts["Text_Dialogue3"]->height * 0.3) },
			texts["Text_Dialogue3"], true);
		Render_DrawQuad_Texture({ (int)(235 + (texts["Text_You"]->width / 2)), (int)((texts["Text_You"]->height / 2) +
									Window_GetHeight() - (images["Textbox"]->height) - 45) },
			{ (unsigned int)(texts["Text_You"]->width * 0.4), (unsigned int)(texts["Text_You"]->height * 0.4) },
			texts["Text_Bill"]);

		RenderState();

		break;

	case 4:
		if (GetMouseButtonPressed(Mouse_LeftButton) and cooldown == 0) // Next.
		{
			state_event = false;
			state = 5;
			cooldown = cooldown_max;
			break;
		}

		PreRenderState();

		Render_DrawQuad_Texture({ (int)(images["WhiteHouse"]->width / 2), (int)(images["WhiteHouse"]->height / 2) },
			{ (images["WhiteHouse"]->width), (images["WhiteHouse"]->height) },
			images["WhiteHouse"]);

		Render_DrawQuad_Texture({ (int)(Window_GetWidth() / 2), (int)(Window_GetHeight() - (images["BillClinton"]->height / 2)) },
			{ (images["BillClinton"]->width), (images["BillClinton"]->height) },
			images["BillClinton"]);

		Render_DrawQuad_Texture({ (int)(images["Textbox"]->width / 2), (int)((images["Textbox"]->height / 2) +
									Window_GetHeight() - (images["Textbox"]->height)) },
			{ (images["Textbox"]->width), (images["Textbox"]->height) },
			images["Textbox"]);
		Render_DrawQuad_Texture({ (int)(195),
			(int)(Window_GetHeight() - (images["Textbox"]->height) + 50) },
			{ (unsigned int)(texts["Text_Choices"]->width * 0.3), (unsigned int)(texts["Text_Choices"]->height * 0.3) },
			texts["Text_Choices"], true);

		RenderState();

		break;

	case 5:
		if (state_event == false)
		{
			Mixer_StopMusic();

			state_event = true;
		}

		if (GetMouseButtonPressed(Mouse_LeftButton) and cooldown == 0) // Next.
		{
			state_event = false;
			state = 6;
			cooldown = 1000;
			break;
		}

		PreRenderState();

		Render_DrawQuad_Texture({ (int)(Window_GetWidth() / 2),
			(int)(Window_GetHeight() / 2) },
			{ (unsigned int)(texts["Text_Dialogue999"]->width * 0.3), (unsigned int)(texts["Text_Dialogue999"]->height * 0.3) },
			texts["Text_Dialogue999"]);

		RenderState();

		break;
	case 6:
		if (GetMouseButtonPressed(Mouse_LeftButton) and cooldown == 500) // Next.
		{
			state = 7;
			break;
		}

		if (cooldown == 0)
			state = 7;

		PreRenderState();

		Render_DrawQuad_Texture({ (int)(Window_GetWidth() / 2),
			(int)(Window_GetHeight() / 2) },
			{ (unsigned int)(texts["Text_Dialogue-1"]->width * 0.3), (unsigned int)(texts["Text_Dialogue-1"]->height * 0.3) },
			texts["Text_Dialogue-1"]);

		RenderState();

		break;

	case 7:
		App_Quit();
	}
}

void Program::Finalise()
{
	for (auto& m : images)
		Render_DeleteTexture(m.second);
	for (auto& m : texts)
		Render_DeleteTexture(m.second);
	for (auto& m : audios)
		Mixer_FreeMusic(m.second);
}

void Program::input()
{	
	//if (GetKeyDown(SDL_SCANCODE_ESCAPE) == true)
	//{
	//	App_Quit();
	//}
	//if (GetMouseButtonPressed(Mouse_LeftButton))
	//{
	//	App_Quit();
	//}
}