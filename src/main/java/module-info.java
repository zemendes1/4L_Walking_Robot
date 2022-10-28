module com.example.trabalho {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.trabalho to javafx.fxml;
    exports com.example.trabalho;
}