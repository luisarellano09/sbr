import 'package:flutter/material.dart';
import './MainPage.dart';

void main() => runApp(new ApplicationSBR());

class ApplicationSBR extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'App Name',
      home: MainPage()
      );
  }
}