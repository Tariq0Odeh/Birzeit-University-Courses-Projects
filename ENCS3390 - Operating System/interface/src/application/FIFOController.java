package application;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;

import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;

public class FIFOController {
	private Stage stage;
	 private Scene scene;
	 private Parent root;
	 
	@FXML
	private TextField tf1;
	@FXML
	private Label l11;
	@FXML
	private TextField tf11;
	@FXML
	private Label l111;
	@FXML
	private Label l1;
	@FXML
	private Label l2;
	@FXML
	private Label l3;
	@FXML
	private Label l4;
	@FXML
	private Label l5;
	@FXML
	 TextArea ta ;
	
	

	public void switchToScene1(ActionEvent event) throws IOException {
		  root = FXMLLoader.load(getClass().getResource("menu.fxml"));
		  stage = (Stage)((Node)event.getSource()).getScene().getWindow();
		  scene = new Scene(root);
		  stage.setScene(scene);
		  stage.show();
		  stage.setTitle("Menu");
		 }
		 public void select(Event e) {
			/* String select = co.getSelectionModel().getSelectedItem().toString();*/
			 //l1.setText(select);
			 String s1 = tf1.getText();
			 l11.setText(s1);
			 String s2 = tf11.getText();
			 l111.setText(s2);
			 
			
		 }
		 public void run(Event e) {
				 
				
			 }
}
