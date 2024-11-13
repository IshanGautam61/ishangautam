/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author ishan
 */
import java.sql.*;
import javax.swing.JOptionPane;

public class javaconnect {
 Connection conn;
 public static Connection ConnecrDb(){
     try{
         Class.forName("org.sqlite.JDBC");
         Connection conn=DriverManager.getConnection("jdbc:sqlite:C:\\Bike Software\\Account.db");
         return conn;        

                 
         
     }catch(Exception e){
         JOptionPane.showMessageDialog(null, e);
         return null;
     }
     
 }
    
}
