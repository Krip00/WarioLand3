#include <QDir>
#include "Sounds.h"

using namespace WL3;

Sounds* Sounds::instance()
{
	static Sounds uniqueInstance;
	return &uniqueInstance;
}

Sounds::Sounds()
{
	QStringList sound_files = QDir(":/sounds/").entryList(QStringList() << "*.wav", QDir::Files);
	for (auto& f : sound_files)
		_sounds[QFileInfo(f).baseName().toStdString()] = new QSound(QString(":/sounds/") + f);
}

void Sounds::play(const std::string& id, bool loop)
{
	if (_sounds.find(id) != _sounds.end())
	{
		_running = true;
		if (loop && !isFinished(id))
			stop(id);
		_sounds[id]->play();
		if (loop)
			_sounds[id]->setLoops(QSound::Infinite);
	}
}

void Sounds::stop(const std::string& id)
{
	if (_sounds.find(id) != _sounds.end() && !_sounds[id]->isFinished())
	{
		tostop = _sounds[id];
		start();
        _running = false;
	}

}

bool Sounds::isFinished(const std::string& id)
{
	if (_sounds.find(id) != _sounds.end())
		return _sounds[id]->isFinished();
	else
		return true;
}

// ferma i suoni in un nuovo thread
void Sounds::run()
{
	if (tostop)
	{
		tostop->stop();
		tostop = 0;
	}
}
