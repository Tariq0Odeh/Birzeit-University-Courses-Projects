package application;

import java.io.IOException;

import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class menuController {
	private Stage stage;
	 private Scene scene;
	 private Parent root;
	 
	 @FXML
	 private TextField mtf;
	 
	
	public void switchToRR(ActionEvent event) throws IOException {
		  root = FXMLLoader.load(getClass().getResource("RR.fxml"));
		  stage = (Stage)((Node)event.getSource()).getScene().getWindow();
		  scene = new Scene(root);
		  stage.setScene(scene);
		  stage.setTitle("RR algorithm page");
		  stage.show();
		 }
	public void switchToFIFO(ActionEvent event) throws IOException {
		  root = FXMLLoader.load(getClass().getResource("FIFO.fxml"));
		  stage = (Stage)((Node)event.getSource()).getScene().getWindow();
		  scene = new Scene(root);
		  stage.setScene(scene);
		  stage.setTitle("FIFO algorithm page");
		  stage.show();
		 }
	public void switchToLRU(ActionEvent event) throws IOException {
		  root = FXMLLoader.load(getClass().getResource("LRU.fxml"));
		  stage = (Stage)((Node)event.getSource()).getScene().getWindow();
		  scene = new Scene(root);
		  stage.setScene(scene);
		  stage.setTitle("LRU algorithm page");
		  stage.show();
		 }
	public void run(Event e) {
		 
		
	 }

}
