
#include "TestControl.h"
#include "TextArea.h"
#include "FlowPanel.h"
#include "Cuwindow.h"


    // int testPrintTextAreas();
    // int testPrintFlowPanels();
    // int testTextAreasinFlowPanel();

    // // Integration tests for CuWindow
    // int mwTestFlowPanels();
    // int mwTestTextAreas();

    // void testRenderWindow();

    // void studentTests();

vector<string> TestControl::menu ={
    "Student tests\n",
    "TextArea test",
    "FlowPanel test",
    "TextArea in FlowPanel test",
    "FlowPanel in CuWindow test\n",
    
    "Test all and get mark\n",
    "Flowlayout Render test\n\nMemory tests - use valgrind:\n",
    "FlowPanel Memory tests",
    "CuWindow Memory tests\n"
    
    
};


void TestControl::launch(){
    //get input, launch the appropriate test
    int choice = -1;

    while (choice!= 0){
        view.menu(menu, choice);
        switch(choice){
            case 1: studentTests(); break;
            case 2: testTextAreas(); break;
            case 3: testFlowPanels(); break;
            case 4: testTextAreasinFlowPanel(); break;
            case 5: testFlowPanelsinWindow(); break;
            case 6: cout<<"Total score: "<<testTextAreas() + testFlowPanels() + testTextAreasinFlowPanel() + testFlowPanelsinWindow()<<"/18"<<endl; break;
            case 7: testRenderWindow(); break;
            case 8: testFlowPanelMemory(); break;
            case 9: testWindowMemory(); break;
        }
    }
}

void TestControl::studentTests(){
    cout<<"Student tests"<<endl;

{
    RGB colour(0, 0, 255);  // change this to your favourite colour
    CuWindow window("Test", 800, 800, colour);

    FlowPanel *panel1 = new FlowPanel(0, 0, 800, 600, "FlowPanel 1");


    TextArea* textArea1 = new TextArea({10, 10, 80, 50}, "ta1","TextArea*1hereisalongstring");
    TextArea* textArea2 = new TextArea({10, 70, 280, 150}, "ta2","TextArea* 2");
    TextArea* textArea3 = new TextArea({10, 130, 280, 70}, "ta3","TextArea* 3");
    TextArea* textArea4 = new TextArea({80, 210, 180, 90}, "ta4","TextArea* 4 here is a long string, in fact this is a very long string, let's see what happens");
    TextArea* textArea5 = new TextArea({80, 400, 180, 90}, "ta5","TextArea* 5 here is a long string, in fact this is a very long string, let's see what happens");
    TextArea* textArea6 = new TextArea({80, 400, 480, 90}, "ta6","TextArea* 6"); 


    panel1->addTextArea(textArea1);
    panel1->addTextArea(textArea2);
    panel1->addTextArea(textArea3);
    panel1->addTextArea(textArea4);
    panel1->addTextArea(textArea5);
    panel1->addTextArea(textArea6);

    window.addPanel(panel1);


    cout<<"CuWindow render test"<<endl<<endl;

    
    window.draw();

    cout<<"Window rendered, please check if it looks correct (see specification for details)"<<endl;
    tester.pressEnterToContinue();
    tester.pressEnterToContinue(); // sigh, input buffers
    }

    
  {  RGB windowColor(200, 200, 200);
    CuWindow window("Test Window", 900, 700, windowColor);

    // Creating two different FlowPanels
    FlowPanel* panel1 = new FlowPanel(0, 0, 450, 700, "Left Panel");
    FlowPanel* panel2 = new FlowPanel(450, 0, 450, 700, "Right Panel");

   
    // TextAreas in panel1
    TextArea* textArea1 = new TextArea({10, 10, 120, 50}, "ta1", "Short Text");
    TextArea* textArea2 = new TextArea({10, 70, 200, 100}, "ta2", "This is a longer string to check how text wraps.");
    TextArea* textArea3 = new TextArea({10, 180, 200, 70}, "ta3", "Multi-line\nText Area Test");

    // TextAreas in panel2
    TextArea* textArea4 = new TextArea({20, 20, 300, 100}, "ta4", "Very long string that should wrap inside the panel correctly.");
    TextArea* textArea5 = new TextArea({20, 150, 250, 100}, "ta5", "Another long text with more words to check behavior.");
    TextArea* textArea6 = new TextArea({20, 300, 250, 50}, "ta6", "Last TextArea.");

    // Changing individual text colors
    textArea1->setFill(RGB(255, 255, 100)); // Yellow background
    textArea2->setFill(RGB(150, 255, 150)); // Light green background
    textArea3->setFill(RGB(255, 150, 150)); // Light red background

    textArea4->setFill(RGB(200, 255, 200)); // Soft green
    textArea5->setFill(RGB(220, 220, 250)); // Light purple
    textArea6->setFill(RGB(255, 255, 255)); // White

    // Add TextAreas to respective panels
    panel1->addTextArea(textArea1);
    panel1->addTextArea(textArea2);
    panel1->addTextArea(textArea3);

    panel2->addTextArea(textArea4);
    panel2->addTextArea(textArea5);
    panel2->addTextArea(textArea6);

    // Add panels to the window
    window.addPanel(panel1);
    window.addPanel(panel2);

    cout << "Rendering window with new configuration..." << endl << endl;
    
    // Draw the window
    window.draw();

    cout << "Window rendered. Check for layout correctness." << endl;
    tester.pressEnterToContinue();
    tester.pressEnterToContinue();
  }

{
    RGB windowColor(220, 220, 220);
    CuWindow window("Test Layout", 1000, 700, windowColor);

    // Create Three FlowPanels (Left, Right, Bottom)
    FlowPanel* panel1 = new FlowPanel(0, 0, 500, 500, "Top Left Panel");
    FlowPanel* panel2 = new FlowPanel(500, 0, 500, 500, "Top Right Panel");
    FlowPanel* panel3 = new FlowPanel(0, 500, 1000, 200, "Bottom Panel");

    
    // Create TextAreas with different sizes and alignments
    TextArea* textArea1 = new TextArea({20, 20, 200, 60}, "ta1", "Short Text Area 1");
    TextArea* textArea2 = new TextArea({20, 100, 300, 100}, "ta2", "Medium-sized Text. Checking if it stays within limits.");
    TextArea* textArea3 = new TextArea({20, 250, 400, 50}, "ta3", "Long TextArea wrapping test: This text should wrap properly inside the rectangle.");

    TextArea* textArea4 = new TextArea({20, 20, 250, 80}, "ta4", "Panel 2: Another test");
    TextArea* textArea5 = new TextArea({20, 120, 300, 80}, "ta5", "Another example of a wrapped text field.");
    TextArea* textArea6 = new TextArea({20, 230, 300, 60}, "ta6", "Panel 2 - Last Box");

    TextArea* textArea7 = new TextArea({50, 20, 500, 80}, "ta7", "This bottom panel is much wider and should be able to display longer text.");
    TextArea* textArea8 = new TextArea({50, 120, 300, 50}, "ta8", "Panel 3 - Secondary Info");

    // Change text area background colors
    textArea1->setFill(RGB(255, 255, 100)); // Yellow
    textArea2->setFill(RGB(150, 255, 150)); // Light Green
    textArea3->setFill(RGB(255, 180, 180)); // Light Red

    textArea4->setFill(RGB(200, 220, 255)); // Soft Blue
    textArea5->setFill(RGB(220, 220, 250)); // Light Purple
    textArea6->setFill(RGB(255, 255, 255)); // White

    textArea7->setFill(RGB(230, 230, 180)); // Light Beige
    textArea8->setFill(RGB(200, 240, 255)); // Light Cyan

    // Add TextAreas to respective panels
    panel1->addTextArea(textArea1);
    panel1->addTextArea(textArea2);
    panel1->addTextArea(textArea3);

    panel2->addTextArea(textArea4);
    panel2->addTextArea(textArea5);
    panel2->addTextArea(textArea6);

    panel3->addTextArea(textArea7);
    panel3->addTextArea(textArea8);

    // Add panels to the window
    window.addPanel(panel1);
    window.addPanel(panel2);
    window.addPanel(panel3);

    cout << "Rendering window with new layout..." << endl << endl;

    // Draw the window
    window.draw();

    cout << "Window rendered. Check for layout correctness." << endl;
    tester.pressEnterToContinue();

}

{
// Set the window background color (dark gray)
    RGB windowColor(50, 50, 50);
    CuWindow window("Color Test Layout", 1000, 700, windowColor);

    // Create Three FlowPanels (Top, Middle, Bottom)
    FlowPanel* panel1 = new FlowPanel(0, 0, 1000, 200, "Top Panel");
    FlowPanel* panel2 = new FlowPanel(0, 200, 500, 300, "Left Panel");
    FlowPanel* panel3 = new FlowPanel(500, 200, 500, 300, "Right Panel");

    
    // Create TextAreas with different colors and texts
    TextArea* textArea1 = new TextArea({20, 20, 250, 60}, "ta1", "Header Text");
    TextArea* textArea2 = new TextArea({300, 20, 400, 100}, "ta2", "Large Title Text, should be visible clearly.");
    TextArea* textArea3 = new TextArea({20, 100, 600, 60}, "ta3", "Additional Information about the header.");

    TextArea* textArea4 = new TextArea({20, 20, 200, 80}, "ta4", "Left Panel Content 1");
    TextArea* textArea5 = new TextArea({20, 120, 400, 80}, "ta5", "More details inside the Left Panel.");
    TextArea* textArea6 = new TextArea({20, 230, 450, 50}, "ta6", "Summary of Left Panel content.");

    TextArea* textArea7 = new TextArea({20, 20, 300, 80}, "ta7", "Right Panel Info 1");
    TextArea* textArea8 = new TextArea({20, 120, 400, 100}, "ta8", "Right Panel detailed description.");
    TextArea* textArea9 = new TextArea({20, 250, 300, 50}, "ta9", "Quick Notes on Right Panel.");

    // Changing text area background colors for visibility
    textArea1->setFill(RGB(255, 255, 150)); // Light Yellow
    textArea2->setFill(RGB(200, 200, 255)); // Light Blue
    textArea3->setFill(RGB(255, 200, 200)); // Light Red

    textArea4->setFill(RGB(180, 255, 180)); // Soft Green
    textArea5->setFill(RGB(220, 220, 250)); // Light Purple
    textArea6->setFill(RGB(255, 255, 255)); // White

    textArea7->setFill(RGB(255, 180, 250)); // Pinkish
    textArea8->setFill(RGB(180, 255, 255)); // Cyan
    textArea9->setFill(RGB(200, 230, 180)); // Olive Green

    // Add TextAreas to respective panels
    panel1->addTextArea(textArea1);
    panel1->addTextArea(textArea2);
    panel1->addTextArea(textArea3);

    panel2->addTextArea(textArea4);
    panel2->addTextArea(textArea5);
    panel2->addTextArea(textArea6);

    panel3->addTextArea(textArea7);
    panel3->addTextArea(textArea8);
    panel3->addTextArea(textArea9);

    // Add panels to the window
    window.addPanel(panel1);
    window.addPanel(panel2);
    window.addPanel(panel3);

    cout << "Rendering window with a new color scheme..." << endl << endl;

    // Draw the window
    window.draw();

    cout << "Window rendered. Check if colors and layout appear as expected." << endl;
    tester.pressEnterToContinue();



}

    cout<<"No tests found"<<endl;
    // Make a window, try stuff out
    // RGB colour(0, 255, 0);  // change this to your favourite colour
    // CuWindow window("Test", 600, 600, colour);

    // make and add panels, add textAreas to panels, etc
    // You should test, at least, different TextArea colours, different Window colours, 
    // and different placements of FlowPanels and TextAreas. There should be at least 
    // 4 different configurations of FlowPanels and TextAreas in your test. Each configuration must have
    // at least 2 FlowPanels and 2 TextAreas.

    // You can use tester.pressEnterToContinue() to pause the program between configurations
}


/*
* Panel tests:
    Add to panel (at back), print, ensure order
    Add to panel at index, print, ensure order
    Remove from panel at index, print, ensure order
CuWindow tests:
    These are currently unchanged I beleive. 
* Panel Memory tests:
    Add to Panel, remove from Panel, printTAs, delete TA, print TAs
    Add to Panel, remove from Panel, change, add again, print
    Add to Panel, change TA, ensure it is changed (Should we test this?)
    Make sure things are in the Panel and use Valgrind
    Make a deep copy of the Panel, delete one and print the other
  CuWindow Memory tests
    Add to window, remove from window, print Panels, delete print Panels
    Add to Window, remove from Window, change, add again, print
    Add to Window, change TA, ensure it is changed (Should we test this?)
    Make sure things are in the Window and use Valgrind

*/


int TestControl::testTextAreas(){
    string labels[5] = {"TextArea 1", "TextArea 2", "TextArea 3", "TextArea 4", "TextArea 5"};
    string ids[5] = {"ta1", "ta2", "ta3", "ta4", "ta5"};
    TextArea* textAreas[5];
    string ycoords[5] = {"10", "70", "130", "190", "250"};
    string widths[5] = {"20", "31", "42", "53", "64"};
    for (int i = 0; i < 5; i++){
        textAreas[i] = new TextArea(10 + 10*i, 10 + 60*i, 20+11*i, 50, ids[5], labels[i]);
    }

    cout<<"TextArea print test"<<endl<<endl;

    tester.initCapture();
    for (int i = 0; i < 5; i++){
        textAreas[i]->print();
    }
    tester.endCapture();

    int score = 0;
    int error = 0;
    tester.findInOrder({0,1,2,3,4}, labels, error);

    if (error == 0){
        cout<<"Label printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Label printing test failed"<<endl;
    }


    error = 0;

    tester.findInOrder({0,1,2,3,4}, widths, error);

    if (error == 0){
        cout<<"Width printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Width printing test failed"<<endl;
    }

    cout<<"TextArea print test score: "<<score<<"/2"<<endl<<endl;

    cout<<"Deleting textAreas"<<endl;

    for (int i = 0; i < 5; i++){
        delete textAreas[i];
    }

    return score;
}

int TestControl::testFlowPanels(){
    string ids[5] = {"FlowPanel 1", "FlowPanel 2", "FlowPanel 3", "FlowPanel 4", "FlowPanel 5"};
    FlowPanel* panels[5];
    string ycoords[5] = {"10", "70", "130", "190", "250"};
    string widths[5] = {"20", "31", "42", "53", "64"};
    for (int i = 0; i < 5; i++){
        panels[i] = new FlowPanel(10 + 10*i, 10 + 60*i, 20+11*i, 50, ids[i]);
    }

    cout<<"FlowPanel print test"<<endl<<endl;

    tester.initCapture();
    for (int i = 0; i < 5; i++){
        panels[i]->print();
    }
    tester.endCapture();

    int score = 0;
    int error = 0;
    tester.findInOrder({0,1,2,3,4}, ids, error);

    if (error == 0){
        cout<<"ID printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"ID printing test failed"<<endl;
    }

    error = 0;
    tester.findInOrder({0,1,2,3,4}, ycoords, error);

    if (error == 0){
        cout<<"Y coordinate printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Y coordinate printing test failed"<<endl;
    }

    error = 0;

    tester.findInOrder({0,1,2,3,4}, widths, error);

    if (error == 0){
        cout<<"Width printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Width printing test failed"<<endl;
    }

    cout<<"FlowPanel print test score: "<<score<<"/3"<<endl<<endl;

    cout<<"Deleting FlowPanels"<<endl;

    for (int i = 0; i < 5; i++){
        delete panels[i];
    }

    return score;
}

int TestControl::testTextAreasinFlowPanel(){
    FlowPanel panel(10, 10, 200, 200, "FlowPanel 1");
    vector<string> ids = {"ta1", "ta2", "ta3", "ta4", "ta5","ta6"};
    vector<string> text = {"TextArea 1", "TextArea 2", "TextArea 3", "TextArea 4", "TextArea 5", "TextArea 6"};
    Rectangle rects[6] = {{10, 10, 80, 50}, {10, 50, 80, 50}, {10, 130, 80, 50}, {80, 130, 80, 50}, {100, 130, 80, 50}, {100, 180, 80, 50}};
    TextArea* textAreas[6];

    for (int i = 0; i < 6; i++){
        textAreas[i] = new TextArea(rects[i], ids[i], text[i]);
        panel.addTextArea(textAreas[i]);
    }


    cout<<"FlowPanel textAreas test"<<endl<<endl;

    tester.initCapture();
    panel.printTextAreas();
    tester.endCapture();

    int score = 0;
    int error = 0;
    tester.findInOrder(text, error);

    if (error == 0){
        cout<<"Correct text found in order, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all text found, or not in order, test failed"<<endl;
    }

    cout<<"Removing textArea 3"<<endl<<endl;
    TextArea* removed = panel.removeTextArea("ta3");

    error = 0;
    tester.initCapture();
    panel.printTextAreas();
    tester.endCapture();

    error = 0;

    tester.findInOrder({0,1,3,4,5}, text, error);

    if (error == 0){
        cout<<"Correct textAreas found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all TextAreas found after removal, test failed"<<endl;
    }

    error = 0;
    tester.confirmAbsent({"TextArea 3"}, error);

    if (error == 0){
        cout<<"TextArea 3 not found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"TextArea 3 was not removed, test failed"<<endl;
    }

    if (removed != textAreas[2]){
        cout<<"Incorrect TextArea returned (or maybe nullptr), test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 1 mark"<<endl;
        score += 1;
    }

    cout<<"Removing textAreas 1 and 6 by *index*"<<endl<<endl;

    if (panel.removeTextArea(0)!=textAreas[0]){
        cout<<"Incorrect TextArea removed, test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 1 mark"<<endl;
        score += 1;
    }

    if (panel.removeTextArea(3)!=textAreas[5]){
        cout<<"Incorrect TextArea removed, test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 1 mark"<<endl;
        score += 1;
    }

    error = 0;
    tester.initCapture();
    panel.printTextAreas();
    tester.endCapture();

    error = 0;
    tester.findInOrder({"TextArea 2", "TextArea 4"}, error);

    if (error == 0){
        cout<<"TextArea 2 and 4 found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"TextArea 2 or 4 was removed/not found, test failed"<<endl;
    }

    error = 0;

    tester.confirmAbsent({"TextArea 1", "TextArea 6"}, error);

    if (error == 0){
        cout<<"TextArea 1 and 6 not found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"TextArea 1 or 6 was not removed, test failed"<<endl;
    }

    cout<<"FlowPanel textAreas test score: "<<score<<"/8"<<endl<<endl;

    // cout<<endl<<"Deleting removed textAreas, test with valgrind and watch for memory errors on exit"<<endl;

    // delete textAreas[2];
    // delete textAreas[0];
    // delete textAreas[5];

    return score;
}

int TestControl::testFlowPanelMemory(){
    FlowPanel panel(10, 10, 200, 200, "FlowPanel 1");
    vector<string> ids = {"ta1", "ta2", "ta3", "ta4", "ta5","ta6"};
    vector<string> text = {"TextArea 1", "TextArea 2", "TextArea 3", "TextArea 4", "TextArea 5", "TextArea 6"};
    Rectangle rects[6] = {{10, 10, 80, 50}, {10, 50, 80, 50}, {10, 130, 80, 50}, {80, 130, 80, 50}, {100, 130, 80, 50}, {100, 180, 80, 50}};
    TextArea* textAreas[6];

    cout<<"Adding 6 textAreas to FlowPanel"<<endl<<endl;

    for (int i = 0; i < 6; i++){
        textAreas[i] = new TextArea(rects[i], ids[i], text[i]);
        panel.addTextArea(textAreas[i]);
    }


    cout<<"Removing textArea 3"<<endl<<endl;
    panel.removeTextArea("ta3");

    cout<<"Removing textAreas 1 and 6 by *index*"<<endl<<endl;

    panel.removeTextArea(0);

    panel.removeTextArea(3);



    cout<<endl<<"Deleting removed textAreas, test with valgrind and watch for memory errors on exit"<<endl;

    tester.pressEnterToContinue();
    tester.pressEnterToContinue();

    delete textAreas[2];
    delete textAreas[0];
    delete textAreas[5];

    return 0;
 
}


int TestControl::testFlowPanelsinWindow(){
    RGB colour(0, 255, 0);
    CuWindow window("Test", 600, 600, colour);

    FlowPanel* panel1  = new FlowPanel(10, 10, 80, 50, "FlowPanel 1");
    FlowPanel* panel2  = new FlowPanel(10, 50, 80, 50, "FlowPanel 2");
    FlowPanel* panel3  = new FlowPanel(10, 60, 80, 50, "FlowPanel 3");
    FlowPanel* panel4  = new FlowPanel(80, 60, 80, 50, "FlowPanel 4");
    FlowPanel* panel5  = new FlowPanel(100, 60, 80, 50, "FlowPanel 5");
    FlowPanel* panel6  = new FlowPanel(100, 180, 550, 50, "FlowPanel 6");

    TextArea* textArea1 = new TextArea(10, 10, 50, 30,"ta1", "panel 1");
    TextArea* textArea2 = new TextArea(10, 50, 50, 30, "ta2", "panel 2");
    TextArea* textArea3 = new TextArea(10, 60, 50, 30, "ta3", "panel 3");
    TextArea* textArea4 = new TextArea(80, 60, 50, 30, "ta4", "panel 4");
    TextArea* textArea5 = new TextArea(100, 60, 50, 30, "ta5", "panel 5");
    TextArea* textArea6 = new TextArea(100, 180, 50, 30, "ta6", "panel 6");

    panel1->addTextArea(textArea1);
    panel2->addTextArea(textArea2);
    panel3->addTextArea(textArea3);
    panel4->addTextArea(textArea4);
    panel5->addTextArea(textArea5);
    panel6->addTextArea(textArea6);

    window.addPanel(panel1);
    window.addPanel(panel2);
    window.addPanel(panel3);
    window.addPanel(panel4);
    window.addPanel(panel5);
    window.addPanel(panel6);

    cout<<"CuWindow panels test"<<endl<<endl;
   
    window.draw();
    tester.pressEnterToContinue();
    tester.pressEnterToContinue();
    tester.initCapture();
    window.printPanels();
    tester.endCapture();

    int score = 0;
    int error = 0;
    tester.find({"FlowPanel 1", "FlowPanel 3",  "FlowPanel 5"}, error);

    if (error == 0){
        cout<<"Correct panels found, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all FlowPanels found, test failed"<<endl;
    }

    error = 0;

    tester.confirmAbsent({"FlowPanel 2", "FlowPanel 4", "FlowPanel 6"}, error);

    if (error == 0){
        cout<<"FlowPanel 2, 4 and 6 not found, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"FlowPanel 2, 4 or 6 was added but should not be, test failed"<<endl;
    }

    cout<<"Removing FlowPanel 3"<<endl<<endl;
    if (panel3 != window.removePanel("FlowPanel 3")){
        cout<<"Incorrect FlowPanel removed, test failed"<<endl;
    } else {
        cout<<"Correct FlowPanel removed, test passed, 1 mark"<<endl;
        score += 1;
    }


    error = 0;
    tester.initCapture();
    window.printPanels();
    tester.endCapture();

    error = 0;

    tester.find({"FlowPanel 1", "FlowPanel 5"}, error);

    if (error == 0){
        cout<<"Correct panels found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all FlowPanels found after removal, test failed"<<endl;
    }

    error = 0;
    tester.confirmAbsent({"FlowPanel 3"}, error);

    if (error == 0){
        cout<<"FlowPanel 3 not found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"FlowPanel 3 was not removed, test failed"<<endl;
    }

    window.draw();
    tester.pressEnterToContinue();

    cout<<"CuWindow panels test score: "<<score<<"/5"<<endl<<endl;

    return score;
}

int TestControl::testWindowMemory(){
    RGB colour(0, 255, 0);
    CuWindow window("Test", 600, 600, colour);

    FlowPanel* panel1  = new FlowPanel(10, 10, 80, 50, "FlowPanel 1");
    FlowPanel* panel2  = new FlowPanel(10, 50, 80, 50, "FlowPanel 2");
    FlowPanel* panel3  = new FlowPanel(10, 60, 80, 50, "FlowPanel 3");
    FlowPanel* panel4  = new FlowPanel(80, 60, 80, 50, "FlowPanel 4");
    FlowPanel* panel5  = new FlowPanel(100, 60, 80, 50, "FlowPanel 5");
    FlowPanel* panel6  = new FlowPanel(100, 180, 350, 50, "FlowPanel 6");

    TextArea* textArea1 = new TextArea(10, 10, 50, 30,"ta1", "panel 1");
    TextArea* textArea2 = new TextArea(10, 50, 50, 30, "ta2", "panel 2");
    TextArea* textArea3 = new TextArea(10, 60, 50, 30, "ta3", "panel 3");
    TextArea* textArea4 = new TextArea(80, 60, 50, 30, "ta4", "panel 4");
    TextArea* textArea5 = new TextArea(100, 60, 50, 30, "ta5", "panel 5");
    TextArea* textArea6 = new TextArea(100, 180, 50, 30, "ta6", "panel 6");

    panel1->addTextArea(textArea1);
    panel2->addTextArea(textArea2);
    panel3->addTextArea(textArea3);
    panel4->addTextArea(textArea4);
    panel5->addTextArea(textArea5);
    panel6->addTextArea(textArea6);

    window.addPanel(panel1);
    window.addPanel(panel2);
    window.addPanel(panel3);
    window.addPanel(panel4);
    window.addPanel(panel5);
    window.addPanel(panel6);

    cout<<"CuWindow panels test"<<endl<<endl;
   
    window.draw();
    tester.pressEnterToContinue();
    tester.pressEnterToContinue();
    

    cout<<"Removing FlowPanel 3"<<endl<<endl;
    window.removePanel("FlowPanel 3");

    cout<<"Removing FlowPanel 6"<<endl<<endl;
    window.removePanel("FlowPanel 6");


    window.draw();
    tester.pressEnterToContinue();

    cout<<"Making a DEEP COPY of panel 6 and adding it back to the window"<<endl<<endl;

    FlowPanel* panel6copy = new FlowPanel(*panel6);
    window.addPanel(panel6copy);

    cout<<"Deleting original panel 6 and printing / rendering CuWindow"<<endl<<endl;

    delete panel6;

    window.printPanels();
    window.draw();
    tester.pressEnterToContinue();

    cout<<"Deleting removed FlowPanels, test with valgrind and watch for memory errors on exit"<<endl;

    delete panel3;
    delete panel2;
    delete panel4;


    return 0;
}



// deprecated
int TestControl::mwTestTextAreas(){

    RGB red(255, 0, 0);
    CuWindow window("Test", 600, 600, red);
    FlowPanel* panel1 = new FlowPanel(0, 0, 600, 300, "FlowPanel 1");
    FlowPanel* panel2 = new FlowPanel(0, 300, 600, 300, "FlowPanel 2");

    TextArea* textArea1 = new TextArea(10, 10, 80, 50,"ta1", "TextArea 1");
    TextArea* textArea2 = new TextArea(10, 70, 80, 50, "ta2","TextArea 2");
    TextArea* textArea3 = new TextArea(10, 130, 80, 50, "ta3","TextArea 3");
    TextArea* textArea4 = new TextArea(80, 130, 80, 50, "ta4","TextArea 4");

    panel1->addTextArea(textArea1);
    panel1->addTextArea(textArea2);
    panel1->addTextArea(textArea3);
    // panel1.addTextArea(textArea4);

    panel2->addTextArea(textArea1);
    panel2->addTextArea(textArea2);
    // panel2->addTextArea(textArea3);
    panel2->addTextArea(textArea4);

    window.addPanel(panel1);
    window.addPanel(panel2);

    cout<<"CuWindow textAreas test"<<endl<<endl;

    tester.initCapture();
    window.printPanelTextAreas();
    tester.endCapture();

    int error = 0;
    
    int score = 0;

    tester.findInOrder({"TextArea 1", "TextArea 2", "TextArea 3", "TextArea 1", "TextArea 2", "TextArea 4"}, error);

    if (error == 0){
        cout<<"Correct textAreas found in correct order, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all TextAreas found or found out of order, test failed"<<endl;
    }

    panel1->removeTextArea("TextArea 3");
    panel2->removeTextArea("TextArea 4");

    tester.initCapture();
    window.printPanelTextAreas();
    tester.endCapture();

    error = 0;
    tester.findInOrder({"TextArea 1", "TextArea 2", "TextArea 3", "TextArea 1", "TextArea 2", "TextArea 4"}, error);

    if (error == 0){
        cout<<"Copy of FlowPanels were made correctly, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"FlowPanels not copied into CuWindow correctly, test failed"<<endl;
    }

    cout<<"CuWindow textAreas test score: "<<score<<"/2"<<endl<<endl;

    return score;
}

void TestControl::testRenderWindow(){

    RGB colour(0, 255, 0);

    CuWindow window("Test", 600, 600, colour);
    FlowPanel *panel1 = new FlowPanel(0, 0, 600, 300, "FlowPanel 1");
    FlowPanel *panel2 = new FlowPanel(0, 300, 600, 300, "FlowPanel 2");

    TextArea* textArea1 = new TextArea({10, 10, 80, 50}, "ta1","TextArea*1hereisalongstring");
    TextArea* textArea2 = new TextArea({10, 70, 280, 150}, "ta2","TextArea* 2");
    TextArea* textArea3 = new TextArea({10, 130, 280, 70}, "ta3","TextArea* 3");
    TextArea* textArea4 = new TextArea({80, 210, 180, 90}, "ta4","TextArea* 4 here is a long string, in fact this is a very long string, let's see what happens");
    TextArea* textArea5 = new TextArea({80, 210, 180, 90}, "ta5","TextArea* 5 here is a long string, in fact this is a very long string, let's see what happens");

    panel1->addTextArea(textArea1);
    panel1->addTextArea(textArea2);
    panel1->addTextArea(textArea3);
    panel1->addTextArea(textArea4);

    panel2->addTextArea(new TextArea(*textArea1 ));
    panel2->addTextArea(new TextArea(*textArea2 ));
    // panel2->addTextArea(textArea3);
    panel2->addTextArea(textArea5);

    window.addPanel(panel1);
    window.addPanel(panel2);

    cout<<"CuWindow render test"<<endl<<endl;

    
    window.draw();

    cout<<"Window rendered, please check if it looks correct (see specification for details)"<<endl;
    tester.pressEnterToContinue();
    tester.pressEnterToContinue(); // sigh, input buffers

    cout<<"Changing textArea 2, making textArea 3 too high to fit"<<endl;
    textArea2->setText("This is a new string for textArea 2. Let's make it extra long so we can see the wrapping feature");
    textArea3->setHeight(400);

    window.draw();

    cout<<"Window rendered, please check if it looks correct (see specification for details)"<<endl;
    tester.pressEnterToContinue();
    
}

