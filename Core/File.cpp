//
//  C++ Vorlesung
//
//  DHBW Ravensburg Campus Friedrichshafen
//
//  2015
//
//  Jakob Bauer
//  cpp@bauer-sw.de
//
//  http://cpp.bauer-sw.de
//
#include "File.h"

#include <sys/stat.h>
#include <fstream>

namespace Core {

  namespace IO {

    File::File()
    {
    }


    File::~File()
    {
    }

    bool File::exists(const std::string& filename) {
      // Über die Dateistatistik kann herausgefunden werden, ob die Datei existiert.
      // siehe sys/stat.h
      struct stat buffer;
      return stat(filename.c_str(), &buffer) == 0;
    }

    std::streamoff File::getFileSize(const std::string& filename) {
      // Über die Dateistatistik kann u.A. die Dateigröße ermittelt werden.
      // siehe sys/stat.h
      // Alternativ kann auch beim Stream mit tellg(0, std::ios::begin) und tellg(0, std::ios::end)
      // die Streamgröße sprich Dateigröße ermittelt werden.
      // Der Ermittlung über die Statistik ist schneller, als im Stream hin- und her zuspringen.
      struct stat buffer;
      if (stat(filename.c_str(), &buffer) == 0) {
        return buffer.st_size;
      }
      return 0;
    }

    bool File::readContent(const std::string& filename, std::vector<char>& content) {
      // Ermittle Dateigröße
      std::streamoff fileSize = getFileSize(filename);
      // Wenn die Datei leer ist (oder nicht exisitert) kann nichts gelesen werden.
      if (fileSize == 0) {
        return false;
      }

      // Öffne Datei im Binärformat
      std::ifstream f(filename.c_str(), std::ios_base::binary);
      // Prüfe ob beim Öffnen ein Fehler aufgetreten ist
      if (!f.good()) {
        return false;
      }

      // Allokiere soviel Speicher, wie die Datei groß ist
      content.resize(fileSize);

      // Lese den kompletten Dateiinhalt in den vector-Container
      f.read(&content[0], fileSize);

      // Schließe die Datei (im Destruktor von std::ifstream würde dies auch passieren).
      f.close();

      // Gebe wahr zurück, da der Inhalt gelesen werden konnte
      return true;
    }

    bool File::writeContent(const std::string& filename, const std::vector<char>& content) {
      // Öffne Datei zum schreiben im Binärformat
      std::ofstream f(filename.c_str(), std::ios_base::binary);

      // Prüfe ob das Öffnen der Datei (respektive das Erstellen) ein Fehler verursacht hat
      if (!f.good()) {
        return false;
      }

      // Schreibe den kompletten Inhalt
      f.write(&content[0], content.size());

      // Schließe die Datei
      f.close();

      // Gebe wahr zurück
      return true;
    }

  }

}
