//import 'dart:async';
import 'dart:convert' show utf8;

import 'package:control_pad/control_pad.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:control_pad/models/gestures.dart';

class GamePadPage extends StatefulWidget {
  final BluetoothDevice server;
  const GamePadPage({this.server});

  @override
  _GamePadPage createState() => new _GamePadPage();

}

class _GamePadPage extends State<GamePadPage> {
  
  BluetoothConnection connection;

  bool isConnecting = true;
  bool get isConnected => connection != null && connection.isConnected;

  bool isDisconnecting = false;

@override
  void initState() {
    super.initState();

    BluetoothConnection.toAddress(widget.server.address).then((_connection) {
      print('Connected to the device');
      connection = _connection;
      setState(() {
        isConnecting = false;
        isDisconnecting = false;
      });

    }).catchError((error) {
      print('Cannot connect, exception occured');
      print(error);
    });
  }

  @override
  void dispose() {
    // Avoid memory leak (`setState` after dispose) and disconnect
    if (isConnected) {
      isDisconnecting = true;
      connection.dispose();
      connection = null;
    }

    super.dispose();
  }

  writeData(String data) {
    if (data == null) return;

    connection.output.add(utf8.encode(data+"\r\n"));
  }


  @override
  Widget build(BuildContext context, ) {

    JoystickDirectionCallback onDirectionChanged(
        double degrees, double distance) {
      /*String data =
          "Degree : ${degrees.toStringAsFixed(2)}, distance : ${distance.toStringAsFixed(2)}";*/
          String data = "55555555";
          if((degrees > 340.00)||(degrees<10.00)){
            data = "11111111";
          }
          else if((degrees > 80.00)&&(degrees<100.00)){
            data = "22222222";
          }
          else if((degrees > 170.00)&&(degrees<190.00)){
            data = "33333333";
          }
          else if((degrees > 260.00)&&(degrees<280.00)){
            data = "44444444";
          }
          else{
            data = "87654321";
          }
      print(data);
      writeData(data);
    }

    PadButtonPressedCallback padBUttonPressedCallback(
        int buttonIndex, Gestures gesture) {
          String data = "55555555";
          if(buttonIndex == 0){
            data = "66666666";
          }
          else if(buttonIndex == 1)
          {
            data = "77777777";
          }
          else if(buttonIndex == 2){
            data = "88888888";
          }
          else if(buttonIndex == 3){
            data = "99999999";
          }
          else{
            data = "12345678";
          }
      
      print(data);
      writeData(data);
    }


    return Scaffold(
      appBar: AppBar(
        title: Text('GamePad'),
        centerTitle: true,
      ),
      body: Container(
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          children: <Widget>[
                  JoystickView(
                    onDirectionChanged: onDirectionChanged,
                  ),
                  PadButtonsView(
                    padButtonPressedCallback: padBUttonPressedCallback,
                  ),
          ]
        )
      )
    );
  }
}