
package application;
 
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;

public class Main extends Application {
 
 @Override
 public void start(Stage stage) {
  try {

	  //RRController RRController ;
   Parent root = FXMLLoader.load(getClass().getResource("scene1.fxml"));
  
  
   Scene scene = new Scene(root);
   stage.setScene(scene);
   stage.setTitle("Main page");
   stage.show();
  // RRController.l1.setText("vkv");;
   
  
   
  } catch(Exception e) {
   e.printStackTrace();
  }
 } 

 public static void main(String[] args) {
  launch(args);
  
 }
}