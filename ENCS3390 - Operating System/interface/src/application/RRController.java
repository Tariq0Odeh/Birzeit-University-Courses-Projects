package application;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class RRController implements Initializable {

 private Stage stage;
 private Scene scene;
 private Parent root;
 
 @FXML
 Label l1;
 @FXML
 Label l2;
 @FXML
 TextField tf1;
 @FXML
 Label l11;
 @FXML
 TableView tv ;
 @FXML
 TextArea ta ;
 
 
 

 
 public void switchToScene1(ActionEvent event) throws IOException {
  root = FXMLLoader.load(getClass().getResource("menu.fxml"));
  stage = (Stage)((Node)event.getSource()).getScene().getWindow();
  scene = new Scene(root);
  stage.setScene(scene);
  stage.setTitle("Menu");
  stage.show();
 }
 public void select(Event e) {
	/* String select = co.getSelectionModel().getSelectedItem().toString();*/
	 //l1.setText(select);
	 String s1 = tf1.getText();
	 l11.setText(s1);
	 
	
 }
 public void run(Event e) {
	 
		
 }

@Override
public void initialize(URL location, ResourceBundle resources) {
	 
	
	
}

 
}