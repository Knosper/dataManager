## Class "Data":

Overview:
The Data class is a central component of a graphical application, responsible for managing GUI elements, loading and rendering textures, and handling user interactions. It encapsulates the application's data management and rendering logic, providing a cohesive interface for the efficient operation of GUI-related tasks.

Features:

    GUI Initialization: Sets up the initial state and configuration of the graphical user interface.
    Texture Management: Loads and manages textures for UI elements, ensuring efficient memory usage and performance.
    Event Handling: Processes user inputs and interactions, facilitating a responsive and interactive user experience.
    Rendering: Handles the drawing of GUI elements and textures on the screen, supporting various rendering needs.

Public Methods:

    void initializeGUI(): Initializes GUI components and sets up necessary resources.
    GLuint loadImage(const std::string& imagePath): Loads an image from the specified path and returns its texture ID. Returns 0 if loading fails.
    void renderUI(): Renders the user interface elements on the screen.
    void handleEvent(const Event& event): Handles user input events, such as mouse clicks and key presses.
    void setDataBaseInfos(const std::vector<Info>& infos): Updates the internal database information with the provided data.

## Class "DatabaseCrawler"

Overview:
The DatabaseCrawler class is designed to automate the detection of databases within a specified IP range and port range. It leverages network scanning tools like nmap to identify active databases and collect essential information such as database type, host IP, and other relevant details. This class is integral to applications requiring automated database discovery for monitoring, auditing, or management purposes.

Constructor:

    DatabaseCrawler(const std::string& startPort, const std::string& endPort, const std::string& startIp, const std::string& endIp, std::string& type): Initializes the crawler with specific scan parameters.

Destructor:

    ~DatabaseCrawler(): Cleans up resources if necessary upon the destruction of the instance.

Public Methods:

    std::vector<DatabaseInfo> detectDatabases(const Data& data): Initiates the scanning process using the configured parameters and returns a list of detected databases. This method may adjust the scanning strategy based on the database type specified during initialization.

Usage Example:

cpp

std::string startPort = "3306";
std::string endPort = "3306";
std::string startIp = "192.168.1.1";
std::string endIp = "192.168.1.255";
std::string type = "MySQL";
DatabaseCrawler dbCrawler(startPort, endPort, startIp, endIp, type);
std::vector<DatabaseInfo> detectedDatabases = dbCrawler.detectDatabases(dataContext);

Implementation Details:

    The class utilizes nmap for scanning the network. Ensure that nmap is installed and accessible in the environment where this application runs.
    It supports multiple database types, including PostgreSQL, MySQL, and SQLite, with the potential for extension to other types as needed.
    Thread-safe design patterns are employed to handle concurrent scans efficiently.

Best Practices:

    Validate IP ranges and port ranges before initiating a scan to prevent scanning unauthorized networks.
    Use the class in environments where network scanning is legally and ethically permissible.
