// #ifndef _WORM_H_
// #define _WORM_H_

// #include <vector>

// using namespace std;
// class Cworm{
// public:
// 	//std::deque<std::pair<int, int> > worm_body;
//     vector< pair<int , int >> worm_body;
// 	pair<int, int> worm_head;

// 	Cworm();
// 	~Cworm();

//     void worm_draw();
// 	void Grow(int, int);
// 	// void SetHead(int, int);
// 	int  RemoveBody();
// 	void Move();
// 	// bool IsThere(int, int);
// 	// void AddQueue(int);
// };

// Cworm::Cworm(){

// }

// void Cworm::worm_draw()//, char letra )
// {   
//   int x = worm_position[0].first;
//   int y = worm_position[0].second;
//   matrix[x][y] = '0';
 
//   for(int i=1; i<worm_position.size(); i++){
//     matrix[worm_position[i].first][worm_position[i].second] = '#';
//   }
// }

// void Cworm::Grow(int x, int y){
// 	this->worm_body.push_back(make_pair(x, y));
// }

// // void Cworm::SetHead(int _x, int _y){
// // 	this->worm_head = make_pair(_x,_y);
// // 	this->worm_body.push_back(worm_head);
// // }

// int Cworm::RemoveBody(){

// 	int t = worm_body.size()-1;

// 	this->worm_body.clear();
// 	this->worm_body.push_back(worm_head);

// 	return t;
// }

// int key = 0; 
// unsigned a = 20;
// unsigned b = 20;
// void Cworm::Move(){
// 	pair<int, int> t_head;
// 	t_head = this->worm_body.front();
//     key = getch ();
// 	// std::cout << "move worm: " << _move << "\n";
// 	if(!worm_body.empty()){
// 		switch(key){
// 			//'w'
// 			case 119:{
// 				if(t_head.first == 1)
// 					t_head.first = a-2;
// 				else
// 					t_head.first -= 1;
// 				this->worm_body[0] = t_head;
// 				this->worm_body.pop_back();
// 				break;
// 			}
// 			//'s'
// 			case 115:{
// 				if(t_head.first == a-2)
// 					t_head.first = 1;
// 				else
// 					t_head.first += 1;
// 				this->worm_body[0] = t_head;
// 				this->worm_body.pop_back();
// 				break;
// 			}
// 			//'a'
// 			case 97:{
// 				if(t_head.second == 1)
// 					t_head.second = b-2;
// 				else
// 					t_head.second -= 1;
// 				this->worm_body[0] = t_head;
// 				this->worm_body.pop_back();
// 				break;
// 			}
// 			//'d'
// 			case 100:{
// 				if(t_head.second == b-2)
// 					t_head.second = 1;
// 				else
// 					t_head.second += 1;

// 				this->worm_body[0] = t_head;
// 				this->worm_body.pop_back();
// 				break;
// 			}
// 			default:
// 			break;
// 		}

// 		worm_head = t_head;
// 	}	
// }

// // bool Cworm::IsThere(int _r, int _c){
// // 	for(auto pos:worm_body){
// // 		if((pos.first == _r) and (pos.second == _c))
// // 			return true;
// // 	}

// // 	return false;
// // }

// // void Cworm::AddQueue(int t){
// // 	std::pair<int, int> tmp = worm_body.back();

// // 	// std::cout << "AddQueue: " << t << "\n";
// // 	for(int i=0; i<t; i++){
// // 		worm_body.push_back(tmp);
// // 	}
// // }

// Cworm::~Cworm(){

// }

// #endif