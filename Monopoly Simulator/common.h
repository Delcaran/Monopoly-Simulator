#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <queue>
#include <string>
#include <cmath>

// TIPI
enum Caselle { VicoloCorto, Probabilita, VicoloStretto, TassaPatrimoniale, StazioneSUD, BastioniGranSasso, Imprevisti, VialeMonterosa, VialeVesuvio, TransitoPrigione, ViaAccademia, SocietaElettrica,
	CorsoAteneo, PiazzaUniversita, StazioneOVEST, ViaVerdi, CorsoRaffaello, PiazzaDante, Parcheggio, ViaMarcoPolo,  CorsoMagellano, LargoColombo, StazioneNord, VialeCostantino,
	VialeTraiano, SocietaAcquaPotabile, PiazzaGiulioCesare, InPrigione, ViaRoma, CorsoImpero, LargoAugusto, StazioneEST, VialedeiGiardini, TassadiLusso, ParcodellaVittoria, VIA
};

enum Cartellini {
	Altro, VaiPrigione, VaiVia, VaiVicoloCorto, VaiViaAccademia, VaiLargoColombo, VaiStazioneNord, VaiParcoDellaVittoria, TrePassiIndietro
};

// COSTANTI
const int kNumCaselle = 40;
const int kNumImprevisti = 16;
const int kNumProbabilita = 16;

const std::string kNomiCaselle[kNumCaselle] = { "Vicolo Corto", "Probabilità", "Vicolo Stretto", "Tassa Patrimoniale", "Stazione SUD", "Bastioni Gran Sasso", "Imprevisti", "Viale Monterosa",
	"Viale Vesuvio", "Prigione",  "Via Accademia", "Società Elettrica", "Corso Ateneo", "Piazza Università", "Stazione OVEST", "Via Verdi",  "Probabilità", "Corso Raffaello", "Piazza Dante",
	"Parcheggio", "Via Marco Polo", "Imprevisti",  "Corso Magellano", "Largo Colombo", 	"Stazione Nord", "Viale Costantino",  "Viale Traiano", "Società Acqua Potabile", "Piazza Giulio Cesare",
	"In Prigione", "Via Roma", "Corso Impero", "Probabilità", "Largo Augusto", "Stazione EST", "Imprevisti", "Viale dei Giardini", "Tassa di Lusso", "Parco della Vittoria", "VIA"
};

const Caselle kTabellone[kNumCaselle] = { VicoloCorto, Probabilita, VicoloStretto, TassaPatrimoniale, StazioneSUD, BastioniGranSasso, Imprevisti, VialeMonterosa, VialeVesuvio, TransitoPrigione,
	ViaAccademia, SocietaElettrica, CorsoAteneo, PiazzaUniversita, StazioneOVEST, ViaVerdi, Probabilita, CorsoRaffaello, PiazzaDante, Parcheggio, ViaMarcoPolo, Imprevisti, CorsoMagellano, LargoColombo,
	StazioneNord, VialeCostantino, VialeTraiano, SocietaAcquaPotabile, PiazzaGiulioCesare, InPrigione, ViaRoma, CorsoImpero, Probabilita, LargoAugusto, StazioneEST, Imprevisti, VialedeiGiardini, TassadiLusso,
	ParcodellaVittoria, VIA 
};

const Cartellini kMazzoImprevisti[kNumImprevisti] = { Altro, VaiPrigione, VaiVia, VaiVicoloCorto, VaiViaAccademia, VaiStazioneNord, VaiParcoDellaVittoria, TrePassiIndietro,
	Altro, VaiPrigione, VaiVia, VaiVicoloCorto, VaiViaAccademia, VaiStazioneNord, VaiParcoDellaVittoria, TrePassiIndietro
} ;
const Cartellini kMazzoProbabilita[kNumProbabilita] = { Altro, VaiPrigione, VaiVia, VaiViaAccademia, VaiLargoColombo, VaiStazioneNord, VaiParcoDellaVittoria, TrePassiIndietro,
	Altro, VaiPrigione, VaiVia, VaiViaAccademia, VaiLargoColombo, VaiStazioneNord, VaiParcoDellaVittoria, TrePassiIndietro
} ;

// VARIABILI
std::vector<int> casella_player;
std::vector<Cartellini> shuffle_probabilita, shuffle_imprevisti;
std::queue<Cartellini> mazzo_probabilita, mazzo_imprevisti;
int visite_caselle[kNumCaselle] = { 0 };
int conta_prigione; // volte in transito = visite_caselle[Prigione] - conta_prigione;

// FUNZIONI
bool gestisciCartellino(const Cartellini cartellino, int &casella_attuale);
void movePlayer(const int player, const int destinazione);
const int vaiInPrigione();
const Caselle getCasellaPlayer(const int player);

#endif // _COMMON_H_