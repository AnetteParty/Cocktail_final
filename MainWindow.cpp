#include "MainWindow.h"
#include "SecondWindow.h"

class MyApp : public wxApp {

public:   
    bool OnInit();      
};

bool MyApp::OnInit() {
    wxInitAllImageHandlers();
    MainWindow *mainWindow = new MainWindow(NULL);
    mainWindow->SetSize(wxSize(1400, 850));
    mainWindow->CentreOnScreen();
    mainWindow->Show(true);
    return true;

}

wxIMPLEMENT_APP(MyApp);

MainWindow::MainWindow(wxWindow *parent) : wxFrame(parent, wxID_ANY, "Cocktail App", wxDefaultPosition, wxDefaultSize) {

    wxImage image;
    image.LoadFile("images/Primms.jpeg", wxBITMAP_TYPE_JPEG);
    wxImage scaledImage = image.Scale(400, 400);
    wxStaticBitmap *staticBitmap = new wxStaticBitmap(this, wxID_ANY, wxBitmap(scaledImage));

    secondWindow = new SecondWindow(this);
    thirdWindow = new ThirdWindow(this);

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *staticTextSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *titleSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *bodySizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *overallSizer = new wxBoxSizer(wxVERTICAL);

    wxButton *myButtonClose = new wxButton(this, wxID_ANY, "Close", wxPoint(1300, 810), wxDefaultSize);
    wxButton *myButtonNew = new wxButton(this, wxID_ANY, "Add Cocktail");
    wxButton *myButtonShow = new wxButton(this, wxID_ANY, "Add Incredient");
    wxButton *myButtonDelete = new wxButton(this, wxID_ANY, "Delete");
    wxButton *myButtonRefresh = new wxButton(this, wxID_ANY, "Refresh");

    wxStaticText *staticTextName = new wxStaticText(this, wxID_ANY, "");
    wxStaticText *staticTextBeschreibung = new wxStaticText(this, wxID_ANY, "");
    wxStaticText *staticTextZutat = new wxStaticText(this, wxID_ANY, "");

    myButtonShow->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);
    myButtonNew->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonAddClicked, this);
    myButtonDelete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonDeleteClicked, this);
    myButtonClose->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonCloseClicked, this);
    myButtonRefresh->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonRefreshClicked, this);

    sqlite3 *db;
    int rc = sqlite3_open("cocktail_db.db", &db);

    if (rc != SQLITE_OK) {
        wxMessageBox("db says no open");
        return;
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, "SELECT id, name, beschreibung FROM cocktail", -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        wxMessageBox("db says no prepare");
        return;
    }

    listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(500, 400), wxLC_REPORT);
    listCtrl->InsertColumn(0, "ID", 0, 50);
    listCtrl->InsertColumn(1, "Name", 0, 200);
    listCtrl->InsertColumn(2, "Beschreibung", 0 , 250);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *beschreibung = sqlite3_column_text(stmt, 2);
        long index = listCtrl->InsertItem(listCtrl->GetItemCount(), wxString::Format("%d", id));
        listCtrl->SetItem(index, 1, wxString::FromUTF8((const char*)name));
        listCtrl->SetItem(index, 2, wxString::FromUTF8((const char*)beschreibung));
    }

    wxStaticText* staticText = new wxStaticText(this, wxID_ANY, "Your Cocktail Database:");
    wxFont font = staticText->GetFont();
    font.SetPointSize(17);
    staticText->SetFont(font);

    listCtrl->Bind(wxEVT_LIST_ITEM_SELECTED, [this, staticTextName, staticTextBeschreibung, staticTextZutat, staticTextSizer, staticBitmap](wxListEvent& event) {
        long index = event.GetIndex();
        wxString id = listCtrl->GetItemText(index, 0);
        wxString name = listCtrl->GetItemText(index, 1);
        wxString beschreibung = listCtrl->GetItemText(index, 2);
        wxString zutatStr = "";

        staticTextName->SetLabel(name);
        wxFont font = staticTextName->GetFont();
        font.SetPointSize(14);
        staticTextName->SetFont(font);
        staticTextBeschreibung->SetLabel("\nBeschreibung: \n" + beschreibung);

        if (name == "Mai Tai") {
            wxBitmap bitmap("images/MaiTai.jpeg", wxBITMAP_TYPE_JPEG);
            wxImage scaledImage = bitmap.ConvertToImage().Scale(400, 400);
            staticBitmap->SetBitmap(wxBitmap(scaledImage));
        } else if (name == "Cosmopolitan") {
            wxBitmap bitmap("images/Cosmopolitan.jpeg", wxBITMAP_TYPE_JPEG);
            wxImage scaledImage = bitmap.ConvertToImage().Scale(400, 400);
            staticBitmap->SetBitmap(wxBitmap(scaledImage));
        } else if (name == "Margarita") {
            wxBitmap bitmap("images/Margarita.jpeg", wxBITMAP_TYPE_JPEG);
            wxImage scaledImage = bitmap.ConvertToImage().Scale(400, 400);
            staticBitmap->SetBitmap(wxBitmap(scaledImage));
        } else if (name == "Mimosa") {
            wxBitmap bitmap("images/Mimosa.jpeg", wxBITMAP_TYPE_JPEG);
            wxImage scaledImage = bitmap.ConvertToImage().Scale(400, 400);
            staticBitmap->SetBitmap(wxBitmap(scaledImage));
        } else if (name == "Mojito") {
            wxBitmap bitmap("images/Mojito.jpeg", wxBITMAP_TYPE_JPEG);
            wxImage scaledImage = bitmap.ConvertToImage().Scale(400, 400);
            staticBitmap->SetBitmap(wxBitmap(scaledImage));
        } else if (name == "Old Fashioned") {
            wxBitmap bitmap("images/Old Fashioned.jpeg", wxBITMAP_TYPE_JPEG);
            wxImage scaledImage = bitmap.ConvertToImage().Scale(400, 400);
            staticBitmap->SetBitmap(wxBitmap(scaledImage));
        } else if (name == "Pina Colada") {
            wxBitmap bitmap("images/Pina Colada.jpeg", wxBITMAP_TYPE_JPEG);
            wxImage scaledImage = bitmap.ConvertToImage().Scale(400, 400);
            staticBitmap->SetBitmap(wxBitmap(scaledImage));
        } else {
            wxBitmap bitmap("images/Primms.jpeg", wxBITMAP_TYPE_JPEG);
            wxImage scaledImage = bitmap.ConvertToImage().Scale(400, 400);
            staticBitmap->SetBitmap(wxBitmap(scaledImage));
        }

        sqlite3 *db;
        int rc = sqlite3_open("cocktail_db.db", &db);

        if (rc != SQLITE_OK) {
            wxMessageBox("db says no open");
            return;
        }

        sqlite3_stmt *stmt;
        wxString query = wxString::Format("SELECT zutaten.name, cocktail_list.menge, cocktail_list.einheit FROM zutaten INNER JOIN cocktail_list ON zutaten.id = cocktail_list.zutat_id WHERE cocktail_list.cocktail_id = %s", id);
        rc = sqlite3_prepare_v2(db, query.utf8_str(), -1, &stmt, NULL);

        if (rc != SQLITE_OK) {
            wxMessageBox("db says no prepare");
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char *name = sqlite3_column_text(stmt, 0);
            int menge = sqlite3_column_int(stmt, 1);
            const unsigned char *einheit = sqlite3_column_text(stmt, 2);

            zutatStr += wxString::Format("%s %d %s\n", wxString::FromUTF8((const char*)name), menge, wxString::FromUTF8((const char*)einheit));
            staticTextZutat->SetLabel(zutatStr);
        }

        Layout();
    });

    titleSizer->Add(staticText);

    staticTextSizer->Add(staticTextName, 0, wxTOP, 10);
    staticTextSizer->Add(staticTextBeschreibung, 0, wxTOP, 20);
    staticTextSizer->Add(staticTextZutat, 0, wxTOP, 50);

    bodySizer->Add(listCtrl);
    bodySizer->Add(staticBitmap, 0, wxLEFT, 20);
    bodySizer->Add(staticTextSizer, 0, wxLEFT, 20);

    bottomSizer->Add(myButtonNew);
    bottomSizer->Add(myButtonShow, 0, wxLEFT, 10);
    bottomSizer->Add(myButtonDelete, 0, wxLEFT, 10);
    bottomSizer->Add(myButtonRefresh, 0, wxLEFT, 10);
    
    overallSizer->Add(titleSizer, 0, wxALL, 20);
    overallSizer->Add(bodySizer, 0, wxLEFT, 20);
    overallSizer->Add(bottomSizer, 0, wxALL, 20);
    mainSizer->Add(overallSizer);

    SetSizer(mainSizer);
}

void MainWindow::OnButtonClicked(wxCommandEvent &event) {

    SecondWindow *secondWindow = new SecondWindow(NULL);
    thirdWindow->CentreOnScreen();
    secondWindow->Show(true);
}

void MainWindow::OnButtonAddClicked(wxCommandEvent &event) {

    ThirdWindow *thirdWindow = new ThirdWindow(NULL);
    thirdWindow->SetSize(wxSize(1000, 800));
    thirdWindow->CentreOnScreen();
    thirdWindow->Show(true);
}

void MainWindow::OnButtonDeleteClicked(wxCommandEvent& event) {

    long itemIndex = -1;
    itemIndex = listCtrl->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (itemIndex == -1) {
        wxMessageBox("select an item");
        return;
    }

    wxString id = listCtrl->GetItemText(itemIndex);

    sqlite3 *db;
    int rc = sqlite3_open("cocktail_db.db", &db);

    if (rc != SQLITE_OK) {
        wxMessageBox("db says no open");
        return;
    }

    wxString query = wxString::Format("DELETE FROM cocktail WHERE ID=%s", id.c_str());
    rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);

    if (rc != SQLITE_OK) {
        wxMessageBox("db says no delete");
        return;
    }

    UpdateList();
}

void MainWindow::OnButtonRefreshClicked(wxCommandEvent& event) {
    UpdateList();
}

void MainWindow::UpdateList() {

    listCtrl->DeleteAllItems();

    sqlite3 *db;
    int rc = sqlite3_open("cocktail_db.db", &db);

    if (rc != SQLITE_OK) {
        wxMessageBox("db says no open");
        return;
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, "SELECT id, name, beschreibung FROM cocktail", -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        wxMessageBox("db says no prepare");
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *beschreibung = sqlite3_column_text(stmt, 2);
        long index = listCtrl->InsertItem(listCtrl->GetItemCount(), wxString::Format("%d", id));
        listCtrl->SetItem(index, 1, wxString::FromUTF8((const char*)name));
        listCtrl->SetItem(index, 2, wxString::FromUTF8((const char*)beschreibung));     
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void MainWindow::OnButtonCloseClicked(wxCommandEvent& event) {
    //wxMessageBox("Goodbye!");
    this->Close();
}

MainWindow::~MainWindow() {}

