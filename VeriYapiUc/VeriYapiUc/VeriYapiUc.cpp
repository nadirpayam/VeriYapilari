#include <stack>
#include <queue>
#include <iostream> 
#include <chrono>

using namespace std;


int dizi1[] = { 1064,1065,1066,1067,1068,1069,1070,1071,1072,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,2001,2002,2003,2004,2013,2014,2015,3001,3002,3003,3004,3005,3006,3007,3008,3009,3010,3011,3012,3013,3014,3015,3016,3017,3018,3019,3020,3021,3022,3023,3024,3025,3026,3027,3028,3029,3030,3031,3032,3033,3034,3035,3036,3037,3038,3039,3040,3041 }; //agac1 için kullanılacak veriler
int dizi2[] = { 3041,3040,3039,3038,3037,3036,3035,3034,3033,3032,3031,3030,3029,3028,3027,3026,3025,3024,3023,3022,3021,3020,3019,3018,3017,3016,3015,3014,3013,3012,3011,3010,3009,3008,3007,3006,3005,3004,3003,3002,3001,2015,2014,2013,2004,2003,2002,2001,1083,1082,1081,1080,1079,1078,1077,1076,1075,1074,1073,1072,1071,1070,1069,1068,1067,1066,1065,1064 }; //agac2 için kullanılacak veriler
int dizi3[] = { 3039,1074,3010,1082,3016,3005,3008,3014,3015,3023,3025,2002,3021,3035,1077,1065,1069,1073,3011,2004,3020,3001,3030,1076,1081,3031,3040,1071,3013,3029,3036,3027,3033,1070,3038,1068,1080,3037,2014,3003,3007,1072,1066,1083,2015,2003,3018,3024,3034,3009,3012,3019,3028,1078,3017,2001,1079,3041,1067,2013,3026,1064,3004,3022,3006,1075,3032,3002 }; //agac3 için kullanılacak veriler



struct Dugum { //Agacta yer alan her bir dugumun veri yapisi
	int veri; //Dugumde tutulan veri
	Dugum* sag; //Dugumun sag cocuguna isaretci
	Dugum* sol; //Dugumun sol cocuguna isaretci
};



struct IkiliSiralamaAgaci { //Ikili siralama agaci veri yapisi
	Dugum* kok; //Agac kokune isaretci
	void agacKur(int*); //Dizi isaretcisi alir ve dizinin elemanlarini ikili siralama agacina uygun sekilde yerlestirir
	void dugum(Dugum* eklenecek);
	void yazdir(Dugum* p);
};
bool DFS(Dugum*, int); //Ilk derinlik arama fonksiyonu bir agac koku ve aranacak deger parametrelerini alir
bool BFS(Dugum*, int);//Ilk genislik arama fonksiyonu bir agac koku ve aranacak deger parametrelerini alir

int agac;
int main()
{
	IkiliSiralamaAgaci ikili;
	ikili.kok = NULL;
	std::cout << "Arama yapacaginiz agaci seciniz:(1,2,3)\n";
	
	cin >> agac;

	switch (agac) {
	case 1:
		ikili.agacKur(dizi1);
		break;
	case 2:
		ikili.agacKur(dizi2);
		break;
	case 3:
		ikili.agacKur(dizi3);
		break;
	}
	

	std::cout << "Agac " << agac << " icin arama yontemini seciniz : (1->DFS 2->BFS)" << endl;

	int yontem;
	cin >> yontem;
	std::cout << "Arayacaginiz degeri giriniz:\n";
	int ara;
	cin >> ara;
	if (yontem == 1)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		DFS(ikili.kok, ara);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		cout << "Arama suresi  =  " << elapsed.count() << " nano-saniye" << endl;
	}
	else if (yontem == 2)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		BFS(ikili.kok, ara);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		cout << "Arama suresi => " << elapsed.count() << " nano-saniye" << endl;
	}



}



void IkiliSiralamaAgaci::agacKur(int* dizi) {
	for (int i = 0; i < 68; i++) {
		Dugum* d;
		int ptr = dizi[i];
		d = new Dugum;
		d->veri = ptr;
		d->sag = NULL;
		d->sol = NULL;
		dugum(d);
	}
}

void IkiliSiralamaAgaci::dugum(Dugum* eklenecek) {
	Dugum* tara, * yeni;
	tara = kok;
	bool eklendi = false;
	yeni = new Dugum;
	yeni->veri = eklenecek->veri;
	yeni->sol = NULL;
	yeni->sag = NULL;
	if (kok == NULL)
	{
		kok = yeni;
	}
	else {
		while ((tara != NULL) && (!eklendi)) {
			if (yeni->veri < tara->veri) {
				if (tara->sol != NULL)
					tara = tara->sol;
				else {
					tara->sol = yeni;
					eklendi = true;
				}
			}
			else if (yeni->veri > tara->veri) {
				if (tara->sag != NULL)
					tara = tara->sag;
				else {
					tara->sag = yeni;
					eklendi = true;
				}



			}
		}



	}
}
void IkiliSiralamaAgaci::yazdir(Dugum* p) {
	if (p) {
		yazdir(p->sol);
		std::cout << p->veri << " " << std::endl;
		yazdir(p->sag);
	}



}
bool DFS(Dugum* dugum, int deger) {
	Dugum* dfs;
	stack<Dugum*>yigin;
	yigin.push(dugum);
	while (!yigin.empty())
	{
		dfs = yigin.top();
		yigin.pop();
		if (dfs->veri == deger) {
			cout << "Sonuc=>  Veri Bulundu" << endl;
			return true;
		}
		if (dfs->sag) {
			yigin.push(dfs->sag);
		}
		if (dfs->sol) {
			yigin.push(dfs->sol);
		}



	}

	return false;
}
bool BFS(Dugum* dugum, int b)
{
	Dugum* bfs;
	queue<Dugum*>kuyruk;
	kuyruk.push(dugum);
	while (!kuyruk.empty())
	{
		bfs = kuyruk.back();
		kuyruk.pop();
		if (bfs->veri == b) {
			cout << "SONUC=>VERI BULUNDU-------->" << bfs->veri << endl;
			return true;
		}
		if (bfs->sol) {
			kuyruk.push(bfs->sol);
		}
		if (bfs->sag) {
			kuyruk.push(bfs->sag);
		}

	}
	return true;
}