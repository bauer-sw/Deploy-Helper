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
#pragma once

#include "Export.h"

#include <string>
#include <vector>

namespace Core {

  namespace IO {

    /// <summary>Beschreibt eine Klasse, um Dateioperationen auszuführen.</summary>
    /// <remarks>Alle Methoden sind aktuell statisch, da zum jetztigen Zeitpunkt keine Objekte davon notwendig sind.</remarks>
    class CORE_API File {
    public:
      /// <summary>Prüft ob eine Datei existiert.</summary>
      /// <param name="filename">Dateipfad.</param>
      /// <returns>TRUE: Datei existiert FALSE: Datei nicht vorhanden</returns>
      static bool exists(const std::string& filename);

      /// <summary>Gibt die Dateigröße in Byte zurück.</summary>
      /// <param name="filename">Dateipfad.</param>
      /// <returns>Gibt 0 zurück, falls die Datei nicht existiert.</returns>
      static std::streamoff getFileSize(const std::string& filename);

      /// <summary>Liest den kompletten Dateiinhalt in ein Datenfeld.</summary>
      /// <remarks>Es wird ein binärer Dateistream geöffnet.</remarks>
      /// <param name="filename">Dateipfad.</param>
      /// <param name="content">Dateiinhalt wird hierrein geschrieben.</param>
      /// <returns>TRUE: Lesen des Dateiinhaltes war erfolgreich FALSE: Es ist ein Fehler aufgetreten.</returns>
      static bool readContent(const std::string& filename, std::vector<char>& content);

      /// <summary>Schreibt den kompletten Dateiinhalt in ein Datenfeld.</summary>
      /// <remarks>Es wird ein binärer Dateistream geöffnet.</remarks>
      /// <param name="filename">Dateipfad.</param>
      /// <param name="content">Dateiinhalt wird hierrein geschrieben.</param>
      /// <returns>TRUE: Lesen des Dateiinhaltes war erfolgreich FALSE: Es ist ein Fehler aufgetreten.</returns>
      static bool writeContent(const std::string& filename, const std::vector<char>& content);

      // Konstruktor (und Destruktur) sind private, dass kein Objekt erzeugt werden kann.
    private:
      File();
      ~File();
    };
  }
}

