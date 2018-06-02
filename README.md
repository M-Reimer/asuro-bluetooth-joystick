Asuro Bluetooth Joystick (über Android App)
===========================================

Um den Asuro-Roboter (oder den "Nachfolger" AAR-04) via Bluetooth steuern zu können gibt es sowohl eine offizielle App als auch ein offizielles Bluetooth-Modul.

Diese Lösung hat zwei Probleme, weshalb ich nach einer Alternative gesucht habe:
- Die App (zumindest die, die via Play-Store installierbar ist) stürzt bei mir und wohl auch bei zahlreichen anderen Nutzern einfach ab.
- Die verfügbare App ermöglicht keine "natürliche" Steuerung wie man diese von anderen Modellen kennt (Fährt solane man Stick betätigt, steht wenn man alles loslässt)
- Das angebotene Bluetooth-Modul war zumindest mir zu teuer (ca. 35 Euro). Bluetooth-Module für Arduino-Projekte gibt es mittlerweile für um die 6 Euro (inlusive Versand).

Alternative App für Android
---------------------------

Das hier angebotene Projekt nutzt zur Steuerung eine App die eigentlich für mit Arduino aufgerüstete Modellautos gedacht ist:  
https://sites.google.com/site/bluetoothrccar/home/6-Joystick-Control  
https://play.google.com/store/apps/details?id=com.andico.control.joystick

Auch diese hat kleinere Mängel, ist aber stabil, ohne Werbung und bietet die von Modellautos gewohnte Steuerung mit zwei "Joysticks".

Alternative für das Bluetooth-Modul
-----------------------------------

Mein Code sollte auch mit dem "offiziellen" Modul unverändert funktionieren.

Eine mögliche Alternative sind die z.B. via eBay angebotenen Bluetooth-Module (wahlweise HC-05 oder HC-06).

Wie man diese mit geringem Aufwand mit dem Asuro verbindet, habe ich im Wiki genauer beschrieben:

[Bluetooth Modul](https://github.com/M-Reimer/asuro-bluetooth-joystick/wiki/Bluetooth-Modul)
