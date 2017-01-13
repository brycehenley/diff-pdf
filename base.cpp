#include <wx/wxprec.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include "base.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

IMPLEMENT_APP(MainApp) // Initializes the MainApp class and tells our program
// to run it
bool MainApp::OnInit()
{
	// Create an instance of our frame, or window
	MainFrame *MainWin = new MainFrame(_T("diff-pdf"), wxPoint(1, 1), wxSize(400,300));
	MainWin->Show(TRUE); // show the window
	SetTopWindow(MainWin); // and finally, set it as the main window

 return TRUE;
}

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
	EVT_BUTTON ( BUTTON_Close, MainFrame::OnExit ) // Tell the OS to run MainFrame::OnExit when
	EVT_BUTTON ( BUTTON_Open1, MainFrame::OnOpen )
	EVT_BUTTON ( BUTTON_Open2, MainFrame::OnOpen2 )

END_EVENT_TABLE() // The button is pressed

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize
	&size): wxFrame((wxFrame*)NULL,  - 1, title, pos, size)
{
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(new wxButton(this, BUTTON_Open1, "Open File_1"), 0, 0, 0);
	sizer->Add(new wxButton(this, BUTTON_Open2, "Open File_2"), 0, 0, 0);
	sizer->Add(new wxButton(this, BUTTON_Close, "close"), 0, 0, 0);
	SetSizer(sizer);
//HelloWorld = new wxButton(this, BUTTON_Hello, _T("close"),
		// shows a button on this window
// 	wxDefaultPosition, wxDefaultSize, 0);
}
//
void MainFrame::OnExit( wxCommandEvent& event )
{
	Close(TRUE); // Tells the OS to quit running this process
}

const char * filepath1;
const char * filepath2;
char * diff("./diff-pdf --view ");
char cmd[256];

void MainFrame::OnOpen( wxCommandEvent& event )
{
	static const wxChar *FILETYPES = _T(
	"pdf files|*.pdf|"
	"PDF files|*.PDF|"
	"All files|*.*"
	);
	wxFileDialog* openFileDialog =
      new wxFileDialog( this, _("Open file"), "", "", FILETYPES,
                        wxFD_OPEN, wxDefaultPosition);

			if ( openFileDialog->ShowModal() == wxID_OK )
			{
				wxString path1;
				path1.append( openFileDialog->GetDirectory() );
				path1.append( wxFileName::GetPathSeparator() );
				path1.append( openFileDialog->GetFilename() );

				filepath1 = path1.mb_str(wxConvUTF8 );
				printf("%s\n",filepath1);
				strcpy( cmd, diff );
				strcat( cmd, filepath1 );

			}
}
void MainFrame::OnOpen2( wxCommandEvent& event )
{
	static const wxChar *FILETYPES = _T(
	"pdf files|*.pdf|"
	"PDF files|*.PDF|"
	"All files|*.*"
	);
	wxFileDialog* openFileDialog =
      new wxFileDialog( this, _("Open file"), "", "", FILETYPES,
                        wxFD_OPEN, wxDefaultPosition);

			if ( openFileDialog->ShowModal() == wxID_OK )
			{
				wxString path2;
				path2.append( openFileDialog->GetDirectory() );
				path2.append( wxFileName::GetPathSeparator() );
				path2.append( openFileDialog->GetFilename() );

				filepath2 = path2.mb_str(wxConvUTF8 );
				printf("%s\n",filepath2);

				// char * diff("./diff-pdf --veiw ");

				// char cmd[256];
				// strcpy( cmd, diff );
				// strcat( cmd, filepath1 );
				strcat( cmd, " " );
				strcat( cmd, filepath2 );

				printf("%s\n", cmd);
				system(cmd);
			}

	// const char * ss;
	// ss << "./diff-pdf --view " << filepath1 << filepath2;
	// system( ss.str().c_str() );
	// system("./diff-pdf --view " + filepath1 + filepath2);

}
