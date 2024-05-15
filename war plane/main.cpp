#include "thuvien.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"

bool init();  // Thiet lap cua so man hinh
TTF_Font *g_fond_text = NULL; //được sử dụng để lưu font chữ sẽ được sử dụng trong trò chơi

void saveHighScore(int score) {  //lưu điểm cao nhất của người chơi vào file "best_score.txt".
	std::ofstream outfile("best_score.txt");
	outfile << score;
	outfile.close();
}

int loadHighScore() {
	std::ifstream infile("best_score.txt"); // đọc điểm cao nhất từ file "best_score.txt".

	int highscore;
	if (infile.is_open()) {
		infile >> highscore;
		infile.close();
		return highscore;
	}
	return 0; 
}

int  main(int arc, char* argv[])
{

	if(!init())return -1;  //neu loi

	gBkground = SDLCommonFunc::LoadImage("img/bk.png");
	if(gBkground == NULL)return -1;

	// Create MainObject
	MainObject plane_object;
	bool ret = plane_object.LoadImg("img/plane_object.png");		// load ảnh nhân vật
	plane_object.SetRect(100,100); //Thiết lập vị trí ban đầu của máy bay 
	if(ret == NULL) //Kiểm tra xem việc tải hình ảnh của máy bay chính có thành công hay không 
	{
		 printf( "Unable to load image %s! SDL Error: %s\n", "img/plane_object.png", SDL_GetError() );
		return 0;
	}
	

	//Create ExplosionObject
	ExplosionObject exp;		//đại diện cho vụ nổ
	ret = exp.LoadImg("img/exp.png");
	if(ret == NULL) 
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "img/plane_object.png", SDL_GetError() );
		return 0;
	}
	exp.set_clip();

	
	ThreatObject* p_threats = new ThreatObject[THREATS]; // vật cản trong trò chơi.
	for(int t = 0; t < THREATS; t++)
	{
		ThreatObject* p_threat = (p_threats + t);
		if(p_threat)
		{
			ret = p_threat->LoadImg("img/threat.png");
			if(ret == NULL)
			{
				printf( "Unable to load image %s! SDL Error: %s\n", "img/threat.png", SDL_GetError() );
				return 0;
			}

			int rand_y = rand()% 600 + 1; //số ngẫu nhiên rand_y trong khoảng từ 1 đến 600, đại diện cho vị trí y ngẫu nhiên của vật cản trên màn hình.
			if(rand_y > SCREEN_HEIGHT - 250)
			{
				rand_y = SCREEN_HEIGHT * 0.3;
			}

			p_threat->SetRect(SCREEN_WIDTH + t*400, rand_y);		//Thiết lập vị trí ban đầu của vật cản. Vị trí x được cố định là ngoài biên phải của màn hình, và vị trí y được chọn ngẫu nhiên.
			p_threat->set_x_val(1); //Thiết lập tốc độ di chuyển theo chiều ngang cho vật cản

			
			BulletObject* p_bullet = new BulletObject(); // đạn

			p_threat->InitBullet(p_bullet);  //cấu hình đối tượng đạn cho vật cản hiện tại.

		}
	
	}
	bool is_quit = false; //Biến này được sử dụng để kiểm tra liệu người chơi đã thoát khỏi trò chơi hay chưa.
	int speed_screen = 0;  //Ban đầu, màn hình sẽ không di chuyển nên speed_screen được gán giá trị là 0.

	int ret_menu = SDLCommonFunc::ShowMenu(gScreen, g_fond_text); //hiển thị menu trò chơi. 
	if(ret_menu == 1)is_quit = true;

	
	
	TextObject point_game; //đối tượng hiển thị điểm số trong trò chơi.
	point_game.SetColor(TextObject::BLACK_TEXT); 
	point_game.SetRect(550, 10);
	int point = 0; // Biến lưu trữ điểm số của người chơi trong quá trình chơi.

	while(!is_quit)			// Vòng lặp này sẽ tiếp tục chạy cho đến khi người chơi đã chọn thoát khỏi trò chơi hoặc kết thúc màn chơi.
	{
			
				while(SDL_PollEvent(&g_event))
				{
					if(g_event.type == SDL_QUIT){
						is_quit = true;
						break;
					}
				plane_object.HandleInputAction(g_event); // xử lý các sự kiện đầu vào từ người chơi
		}
		
		
		

	
		speed_screen -= SCREEN_SPEED; // Giảm tốc độ di chuyển của màn hình
		SDLCommonFunc::ApplySurface(gBkground, gScreen, speed_screen, 0);        //Hiển thị hình nền của trò chơi trên màn hình, với vị trí được cập nhật liên tục để tạo hiệu ứng di chuyển.
		SDLCommonFunc::ApplySurface(gBkground, gScreen, speed_screen + SCREEN_WIDTH, 0);
		if (speed_screen <= -SCREEN_WIDTH) speed_screen = 0; //Kiểm tra xem đã di chuyển hết hình nền hay chưa. Nếu đã di chuyển hết, thì quay lại vị trí ban đầu để tạo hiệu ứng lặp lại.

		// Make MainObject
		
		plane_object.HandleMove();//xử lý di chuyển của máy bay chính
		plane_object.Show(gScreen); //hiển thị máy bay chính lên màn hình.
		plane_object.MakeBullet(gScreen); // xử lý đạn cho đối tượng chính



		// Make ThreatObject
		for(int tt = 0; tt < THREATS; tt++)
		{
			ThreatObject* p_threat = (p_threats + tt);
			if(p_threat)
			{
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(gScreen);
				if(p_threat->GetRect().x > plane_object.GetRect().x) //Kiểm tra xem vật cản hiện tại đã di chuyển vượt qua máy bay chính hay chưa
				{
					p_threat->MakeBullet(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT); // tạo đạn cho chúng 


					// xử lý va chạm giữa main và bullet_threat 
					std::vector<BulletObject*>bulletT_list = p_threat->GetBulletList(); //Lấy danh sách đạn của vật cản hiện tại.
					for(int  bt = 0; bt < bulletT_list.size(); bt++)
					{
						bool is_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), bulletT_list.at(bt)->GetRect()); //Kiểm tra xem có va chạm giữa máy bay chính và đạn của vật cản hay không.
						if(is_col)
						{

							// thực hiện vụ nổ cho main object 
							for(int ex_m = 0; ex_m < 4; ex_m++)
							{
								int x = (plane_object.GetRect().x + plane_object.GetRect().w * 0.5) - EXPLOSION_WIDTH * 0.5;  // vị trí hiển thị vụ nổ giữa trung tâm của máy bay chính.
								int y = (plane_object.GetRect().y + plane_object.GetRect().h * 0.5) - EXPLOSION_HEIGHT * 0.5;

								exp.set_frame(ex_m);
								exp.SetRect(x, y);
								exp.ShowEx(gScreen);


								if(SDL_Flip(gScreen) == -1)return -1;  //Cập nhật màn hình và kiểm tra lỗi sau khi hiển thị vụ nổ.


							}
							if(point > loadHighScore())saveHighScore(point);

							if(MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK) == IDOK)//Hiển thị thông báo "GAME OVER!" và kết thúc trò chơi nếu người chơi nhấn nút "OK" trên hộp thoại thông báo.
							{
								SDLCommonFunc::CleanUp(); //Giải phóng tài nguyên và thoát khỏi SDL khi kết thúc trò chơi.
								SDL_Quit();
								return -1;
							}
						}
					} 



					// xử lý va chạm giữa main và threat
					bool is_col1 = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
					if(is_col1)
					{

						// thực hiện vụ nổ cho main object 
						for(int ex_m = 0; ex_m < 4; ex_m++)
						{
							int x = (plane_object.GetRect().x + plane_object.GetRect().w * 0.5) - EXPLOSION_WIDTH * 0.5;
							int y = (plane_object.GetRect().y + plane_object.GetRect().h * 0.5) - EXPLOSION_HEIGHT * 0.5;

							exp.set_frame(ex_m);
							exp.SetRect(x, y);
							exp.ShowEx(gScreen);
							

							if(SDL_Flip(gScreen) == -1)return -1;


						}



						// thực hiện vụ nổ cho threat object 
						for(int ex_t = 0; ex_t < 4; ex_t++)
						{
							int x = (p_threat->GetRect().x + p_threat->GetRect().w * 0.5) - EXPLOSION_WIDTH * 0.5;
							int y = (p_threat->GetRect().y + p_threat->GetRect().h * 0.5) - EXPLOSION_HEIGHT * 0.5;

							exp.set_frame(ex_t);
							exp.SetRect(x, y);
							exp.ShowEx(gScreen);

							if(SDL_Flip(gScreen) == -1)
							{
								delete [] p_threats;
								SDLCommonFunc::CleanUp();
								SDL_Quit();
								return -1;
							}
						}

						if(point > loadHighScore())saveHighScore(point);

						if(MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK) == IDOK)
						{
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return -1;
						}
					}



					// xử lý va chạm giữa đạn của main object với threat object
					std::vector<BulletObject*> bulletM_list = plane_object.GetBulletList();// vector chứa con trỏ đến các đối tượng đạn của máy bay chính 
					for(int bm = 0; bm < bulletM_list.size(); bm++)
					{
						bool is_col2 = SDLCommonFunc::CheckCollision(bulletM_list.at(bm)->GetRect(), p_threat->GetRect());// Kiểm tra xem đạn của máy bay chính có va chạm với vật cản không
						if(is_col2) 
						{

							for(int ex_t = 0; ex_t < 4; ex_t++)c
							{
								int x = (p_threat->GetRect().x + p_threat->GetRect().w * 0.5) - EXPLOSION_WIDTH * 0.5;
								int y = (p_threat->GetRect().y + p_threat->GetRect().h * 0.5) - EXPLOSION_HEIGHT * 0.5;

								point += 10;
								exp.set_frame(ex_t);
								exp.SetRect(x, y);
								exp.ShowEx(gScreen);
								if(SDL_Flip(gScreen) == -1)return -1;
							}
							
							bulletM_list.at(bm)->set_is_move(false);
							p_threat->Reset(SCREEN_WIDTH);	

						}

					}
				}
			}
		}
		// Show point_game
		std::string val_str_point = std::to_string(point); //Chuyển điểm số từ kiểu số nguyên sang chuỗi và tạo chuỗi "Score: " để hiển thị điểm số trên màn hình.
		std::string strPoint("Score: ");
		strPoint += val_str_point;

		point_game.SetText(strPoint);
		point_game.CreateText(g_fond_text, gScreen);


		// Update screen
		if(SDL_Flip(gScreen) == -1)return -1;			// Cập nhật màn hình và kiểm tra lỗi sau khi hiển thị tất cả các đối tượng và điểm số
	}


	SDLCommonFunc::CleanUp();
	SDL_Quit();
	c
	return 0;	
}

bool init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)					// khoi tao cac thanh phan cua SDL
	{
		return false;
	}
	gScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,SCREEN_BPP, SDL_SWSURFACE);						// thiet lap cua so video
	if(gScreen == NULL)
	{
		return false;
	}

	if(TTF_Init() == -1) //cho phép sử dụng font trong trò chơi.
	{
		return false;
	}

	g_fond_text = TTF_OpenFont("ttf/dlxfont.ttf",20 );
	if(g_fond_text == NULL)
	{
		return false;

	}

	
	return true;
}

