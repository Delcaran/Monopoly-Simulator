#include "common.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>

int main(int argc, char *argv[])
{
	// mescolo le probabilita e gli imprevisti
	std::srand(static_cast<unsigned int>(std::time(0)));
	for(int p = 0; p < kNumProbabilita; ++p) { shuffle_probabilita.push_back(kMazzoProbabilita[p]); }
	for(int i = 0; i < kNumImprevisti; ++i) { shuffle_imprevisti.push_back(kMazzoImprevisti[i]); }
	std::random_shuffle(shuffle_probabilita.begin(), shuffle_probabilita.end());
	std::random_shuffle(shuffle_imprevisti.begin(), shuffle_imprevisti.end());
	for(std::vector<Cartellini>::iterator p = shuffle_probabilita.begin(); p != shuffle_probabilita.end(); ++p) { mazzo_probabilita.push(*p); }
	for(std::vector<Cartellini>::iterator i = shuffle_imprevisti.begin(); i != shuffle_imprevisti.end(); ++i) { mazzo_probabilita.push(*i); }

	int num_players;
	num_players = 4;
	std::vector<int> turni_consecutivi_prigione(num_players);
	std::vector<int> doppi_consecutivi(num_players);
	for(int p = 0; p < num_players; ++p) { casella_player.push_back(0); }
	for(std::vector<int>::iterator p = turni_consecutivi_prigione.begin(); p != turni_consecutivi_prigione.end(); ++p) { *p = 0; }
	for(std::vector<int>::iterator p = doppi_consecutivi.begin(); p != doppi_consecutivi.end(); ++p) { *p = 0; }

	int num_turns;
	num_turns = num_players * 50;

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
			do {	
				// verifico cosa succede nella casella di arrivo
				switch(kTabellone[casella_nuova]) {
				case Probabilita:
					continua_analisi = gestisciCartellino(mazzo_probabilita.front(), casella_nuova);
					mazzo_probabilita.push(mazzo_probabilita.front());
					mazzo_probabilita.pop();
					break;
				case Imprevisti:
					continua_analisi = gestisciCartellino(mazzo_imprevisti.front(), casella_nuova);
					mazzo_imprevisti.push(mazzo_imprevisti.front());
					mazzo_imprevisti.pop();
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

	// fine simulazione, stampo i risultati
	for(int casella = 0; casella < kNumCaselle; ++casella) {
		std::cout << kNomiCaselle[casella] << "\t\t: "<< visite_caselle[casella] << std::endl;
	}

	int dummy;
	std::cin >> dummy;

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
