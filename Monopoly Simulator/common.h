#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

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
const int kNumCartellini = 16;

const std::string kNomiCaselle[kNumCaselle] = { "Vicolo Corto", "Probabilita'", "Vicolo Stretto", "Tassa Patrimoniale", "Stazione SUD", "Bastioni Gran Sasso", "Imprevisti", "Viale Monterosa",
	"Viale Vesuvio", "Prigione",  "Via Accademia", "Societa' Elettrica", "Corso Ateneo", "Piazza Universita'", "Stazione OVEST", "Via Verdi",  "Probabilita'", "Corso Raffaello", "Piazza Dante",
	"Parcheggio", "Via Marco Polo", "Imprevisti",  "Corso Magellano", "Largo Colombo", 	"Stazione Nord", "Viale Costantino",  "Viale Traiano", "Societa' Acqua Potabile", "Piazza Giulio Cesare",
	"In Prigione", "Via Roma", "Corso Impero", "Probabilita'", "Largo Augusto", "Stazione EST", "Imprevisti", "Viale dei Giardini", "Tassa di Lusso", "Parco della Vittoria", "VIA"
};

const Caselle kTabellone[kNumCaselle] = { VicoloCorto, Probabilita, VicoloStretto, TassaPatrimoniale, StazioneSUD, BastioniGranSasso, Imprevisti, VialeMonterosa, VialeVesuvio, TransitoPrigione,
	ViaAccademia, SocietaElettrica, CorsoAteneo, PiazzaUniversita, StazioneOVEST, ViaVerdi, Probabilita, CorsoRaffaello, PiazzaDante, Parcheggio, ViaMarcoPolo, Imprevisti, CorsoMagellano, LargoColombo,
	StazioneNord, VialeCostantino, VialeTraiano, SocietaAcquaPotabile, PiazzaGiulioCesare, InPrigione, ViaRoma, CorsoImpero, Probabilita, LargoAugusto, StazioneEST, Imprevisti, VialedeiGiardini, TassadiLusso,
	ParcodellaVittoria, VIA 
};

const Cartellini kMazzoImprevisti[kNumCartellini] = { VaiPrigione, VaiPrigione, VaiVia, VaiVia, VaiVicoloCorto, VaiVicoloCorto, Altro, Altro, Altro, Altro, Altro, Altro, Altro, Altro, Altro, Altro } ;
const Cartellini kMazzoProbabilita[kNumCartellini] = { VaiPrigione, VaiPrigione, VaiVia, VaiVia, VaiViaAccademia, VaiViaAccademia, VaiLargoColombo, VaiLargoColombo, VaiStazioneNord, VaiStazioneNord, VaiParcoDellaVittoria,
	VaiParcoDellaVittoria, TrePassiIndietro, TrePassiIndietro, Altro, Altro 
} ;

// VARIABILI
std::vector<int> casella_player;
std::vector<Cartellini> mazzo_probabilita, mazzo_imprevisti;
int visite_caselle[kNumCaselle] = { 0 };
int conta_prigione; // volte in transito = visite_caselle[Prigione] - conta_prigione;

// FUNZIONI
bool gestisciCartellino(const Cartellini cartellino, int &casella_attuale);
void movePlayer(const int player, const int destinazione);
const int vaiInPrigione();
const Caselle getCasellaPlayer(const int player);

#endif // _COMMON_H_