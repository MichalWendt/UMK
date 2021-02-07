module org.example {

    requires javafx.controls;
    requires javafx.fxml;
    requires com.fasterxml.jackson.databind;
    requires org.json;

    opens org.example to javafx.fxml;
    exports org.example;
}