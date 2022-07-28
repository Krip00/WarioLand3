#pragma once

#include <QSound>
#include <QThread>

namespace WL3
{
	class Sounds;
}

class WL3::Sounds : QThread
{
	private:		
        std::map< std::string, QSound*> _sounds; // suoni riconosciuti dal nome del file
        QSound* tostop; // suoni che devono essere stoppati in un nuovo thread
        bool _running;


		Sounds();
	public:
		// singleton
		static Sounds* instance();


        virtual void run(); // metoto astratto implementato da Qt
        bool running(){ return _running; }


        // play/stop suoni
		void play(const std::string & id, bool loop = false);
		void stop(const std::string & id);
		bool isFinished(const std::string & id);
};
