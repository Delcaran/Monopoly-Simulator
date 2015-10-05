#include "common.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <ios>
#include <iomanip>

int main(int argc, char *argv[])
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	int num_players = 1 + (rand() % 10);
	int num_turns = 1 + (rand() % 10000);
	int num_partite = 1 + (rand() % 100);

	switch(argc) {
	case 2: 
		num_players = atoi(argv[1]); 
		break;
	case 3:
		num_players = atoi(argv[1]); 
		num_partite = atoi(argv[2]);
		break;
	case 4:
		num_players = atoi(argv[1]); 
		num_partite = atoi(argv[2]); 
		num_turns = atoi(argv[3]); 
		break;
	default:
		num_players = 1 + (rand() % 10);
		num_partite = 1 + (rand() % 100);
		num_turns = 1 + (rand() % 10000);
		break;
	}

	for(int partita = 0; partita < num_partite; ++partita) {
		// mescolo le probabilita e gli imprevisti
		std::srand(static_cast<unsigned int>(std::time(0)));
		for(int p = 0; p < kNumCartellini; ++p) { 
			mazzo_probabilita.push_back(kMazzoProbabilita[p]);
			mazzo_imprevisti.push_back(kMazzoImprevisti[p]);
		}
		std::random_shuffle(mazzo_probabilita.begin(), mazzo_probabilita.end());
		std::random_shuffle(mazzo_imprevisti.begin(), mazzo_imprevisti.end());

		std::vector<int> turni_consecutivi_prigione(num_players);
		std::vector<int> doppi_consecutivi(num_players);
		for(int p = 0; p < num_players; ++p) { casella_player.push_back(0); }
		for(std::vector<int>::iterator p = turni_consecutivi_prigione.begin(); p != turni_consecutivi_prigione.end(); ++p) { *p = 0; }
		for(std::vector<int>::iterator p = doppi_consecutivi.begin(); p != doppi_consecutivi.end(); ++p) { *p = 0; }

		for(int turn = 0; turn < num_turns; ++turn) {
			for(int player = 0; player < num_players; ++player) {
				int roll_1 = 1 + (rand() % 6);
				int roll_2 = 1 + (rand() % 6);
				int roll = roll_1 + roll_2;
				bool doppio = (roll_1 == roll_2);
				if (doppio) doppi_consecutivi.at(player) += 1;
			
				int casella_attuale = casella_player.at(player);
				// verifico se si trova in prigione
				if(kTabellone[casella_attuale] == InPrigione) {
					if(turni_consecutivi_prigione.at(player) < 3) {
						// meno di tre turni, esce con doppio
						if(!doppio) {
							continue; // niente doppio, salta il turno
						}
					} else {
						// pena scontata, prosegue
						turni_consecutivi_prigione.at(player) = 0;
					}
				} else {
					// non e' in prigione, verifico se ha fatto 3 doppi di fila
					if(doppio) {
						if(doppi_consecutivi.at(player) == 3) {
							// in prigione
							movePlayer(player, vaiInPrigione());
							continue;
						}
					} else {
						doppi_consecutivi.at(player) = 0;
					}
				}

				int casella_arrivo = (casella_attuale + roll) % kNumCaselle;
				movePlayer(player, casella_arrivo);
				bool continua_analisi = true;
				int casella_nuova = casella_arrivo;
				Cartellini estratto;
				do {	
					// verifico cosa succede nella casella di arrivo
					switch(kTabellone[casella_nuova]) {
					case Probabilita:
						estratto = mazzo_probabilita.front();
						continua_analisi = gestisciCartellino(estratto, casella_nuova);
						mazzo_probabilita.push_back(estratto);
						mazzo_probabilita.erase(mazzo_probabilita.begin());
						break;
					case Imprevisti:
						estratto = mazzo_imprevisti.front();
						continua_analisi = gestisciCartellino(estratto, casella_nuova);
						mazzo_imprevisti.push_back(estratto);
						mazzo_imprevisti.erase(mazzo_imprevisti.begin());
						break;
					case InPrigione:
						casella_nuova = vaiInPrigione();
						continua_analisi = false;
						// cosa succede se ho fatto un tiro doppio e sono finito nella casella "InPrigione" ???
						break;
					default: 
						continua_analisi = false;
						break;
					}

					if(casella_player.at(player) != casella_nuova) {
						movePlayer(player, casella_nuova);
					}
				} while(continua_analisi);

				// se ha fatto un doppio tocca di nuovo a questo giocatore
				if(doppio) --player;
			}
		}
	}

	// fine simulazione, stampo i risultati
	std::cout << num_players << " giocatori in " << num_partite << " partite da " << num_turns << " turni." << std::endl;
	for(int casella = 0; casella < kNumCaselle; ++casella) {
		std::cout << std::setw(25) << std::setfill(' ') << std::left << kNomiCaselle[casella] << " : " << std::setw(5) << std::right << visite_caselle[casella];
		if(casella == static_cast<int>(TransitoPrigione)) {
			std::cout << " , di cui in prigione: " << conta_prigione;
		}
		std::cout << std::endl;
	}

	return 0;
}

bool gestisciCartellino(const Cartellini cartellino, int &casella_attuale) {
	int nuova_casella;
	switch(cartellino) {
	case VaiPrigione:
		casella_attuale = vaiInPrigione();
		return false;
		break;
	case VaiVia:
		casella_attuale = VIA;
		return false;
		break;
	case VaiVicoloCorto:
		casella_attuale = VicoloCorto;
		return false;
		break;
	case VaiViaAccademia:
		casella_attuale = ViaAccademia;
		return false;
		break;
	case VaiLargoColombo:
		casella_attuale = LargoColombo;
		return false;
		break;
	case VaiStazioneNord:
		casella_attuale = StazioneNord;
		return false;
		break;
	case VaiParcoDellaVittoria:
		casella_attuale = ParcodellaVittoria;
		return false;
		break;
	case TrePassiIndietro:
		nuova_casella = casella_attuale - 3;
		if(nuova_casella < 0) nuova_casella = kNumCaselle - nuova_casella;
		casella_attuale = nuova_casella % kNumCaselle;
		return true;
		break;
	default: 
		return false;
		break;
	}
}

void movePlayer(const int player, const int destinazione) {
	++visite_caselle[destinazione];
	casella_player.at(player) = destinazione;
}

const int vaiInPrigione() {
	++conta_prigione;
	return kTabellone[TransitoPrigione];
}
