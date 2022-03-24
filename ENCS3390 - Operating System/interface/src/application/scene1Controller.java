
package application;

import java.io.IOException;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class scene1Controller {

 private Stage stage;
 private Scene scene;
 private Parent root;
 
 @FXML
	private Button exit;
 
 public void switchToScene2(ActionEvent event) throws IOException {
  Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
  stage = (Stage)((Node)event.getSource()).getScene().getWindow();
  scene = new Scene(root);
  stage.setScene(scene);
  stage.setTitle("Menu");
  stage.show();
 }
 public void EXIT(ActionEvent event) throws IOException {
	 
	   Stage stage = (Stage) exit.getScene().getWindow();
	    stage.close();
	 }
 
 
 
}