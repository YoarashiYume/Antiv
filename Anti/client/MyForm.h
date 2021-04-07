#pragma once
#include "Messanger.hpp"
#include <string>
#include <vector>
#include <msclr/marshal_cppstd.h>
namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ setBtn;
	private: System::Windows::Forms::TextBox^ pathBox;
	protected:
		HANDLE pipe,pipeBack;
		Messanger* pipeIO;
		Messanger* pipeBackIO;
	private: System::Windows::Forms::Button^ scanBtn;
	private: System::Windows::Forms::Button^ stopSCBtn;
	protected:


	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;



	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::TabControl^ tabControl1;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::TabPage^ tabPage4;

	private: System::Windows::Forms::Button^ quarBtn;

	private: System::Windows::Forms::Button^ delBtn;

	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Button^ mAddBtn;
	private: System::Windows::Forms::TextBox^ mPathBox;
	private: System::Windows::Forms::Button^ mPath;


	private: System::Windows::Forms::ListBox^ listBox2;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog2;
	private: System::Windows::Forms::Button^ mRemMon;
	private: System::Windows::Forms::Button^ aSchBtn;



	private: System::Windows::Forms::Button^ sPathBtn;
	private: System::Threading::Thread^ backThread;

	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog3;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ sPathBox;
	private: System::Windows::Forms::ListBox^ listBox3;
	private: System::Windows::Forms::Button^ sRemSch;
	private: System::Windows::Forms::Button^ sSendSchBtn;
	private: System::Windows::Forms::Button^ bQuarBtn;




	private: System::ComponentModel::IContainer^ components;

	protected:

	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->setBtn = (gcnew System::Windows::Forms::Button());
			this->pathBox = (gcnew System::Windows::Forms::TextBox());
			this->scanBtn = (gcnew System::Windows::Forms::Button());
			this->stopSCBtn = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->bQuarBtn = (gcnew System::Windows::Forms::Button());
			this->quarBtn = (gcnew System::Windows::Forms::Button());
			this->delBtn = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->mRemMon = (gcnew System::Windows::Forms::Button());
			this->mAddBtn = (gcnew System::Windows::Forms::Button());
			this->mPathBox = (gcnew System::Windows::Forms::TextBox());
			this->mPath = (gcnew System::Windows::Forms::Button());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->sSendSchBtn = (gcnew System::Windows::Forms::Button());
			this->sRemSch = (gcnew System::Windows::Forms::Button());
			this->listBox3 = (gcnew System::Windows::Forms::ListBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->sPathBox = (gcnew System::Windows::Forms::TextBox());
			this->aSchBtn = (gcnew System::Windows::Forms::Button());
			this->sPathBtn = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog2 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->folderBrowserDialog3 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->SuspendLayout();
			// 
			// setBtn
			// 
			this->setBtn->Location = System::Drawing::Point(6, 38);
			this->setBtn->Name = L"setBtn";
			this->setBtn->Size = System::Drawing::Size(360, 23);
			this->setBtn->TabIndex = 0;
			this->setBtn->Text = L"Set folder";
			this->setBtn->UseVisualStyleBackColor = true;
			this->setBtn->Click += gcnew System::EventHandler(this, &MyForm::setBtn_Click);
			// 
			// pathBox
			// 
			this->pathBox->Location = System::Drawing::Point(6, 12);
			this->pathBox->Name = L"pathBox";
			this->pathBox->Size = System::Drawing::Size(360, 20);
			this->pathBox->TabIndex = 1;
			// 
			// scanBtn
			// 
			this->scanBtn->Location = System::Drawing::Point(6, 67);
			this->scanBtn->Name = L"scanBtn";
			this->scanBtn->Size = System::Drawing::Size(360, 23);
			this->scanBtn->TabIndex = 2;
			this->scanBtn->Text = L"Start Scan";
			this->scanBtn->UseVisualStyleBackColor = true;
			this->scanBtn->Click += gcnew System::EventHandler(this, &MyForm::scanBtn_Click);
			// 
			// stopSCBtn
			// 
			this->stopSCBtn->Location = System::Drawing::Point(6, 141);
			this->stopSCBtn->Name = L"stopSCBtn";
			this->stopSCBtn->Size = System::Drawing::Size(360, 23);
			this->stopSCBtn->TabIndex = 3;
			this->stopSCBtn->Text = L"Stop Scan";
			this->stopSCBtn->UseVisualStyleBackColor = true;
			this->stopSCBtn->Click += gcnew System::EventHandler(this, &MyForm::stopSCBtn_Click);
			// 
			// textBox2
			// 
			this->textBox2->Enabled = false;
			this->textBox2->Location = System::Drawing::Point(398, 6);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(692, 461);
			this->textBox2->TabIndex = 4;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(6, 106);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(360, 23);
			this->progressBar1->TabIndex = 8;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Location = System::Drawing::Point(12, 13);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1104, 540);
			this->tabControl1->TabIndex = 9;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->stopSCBtn);
			this->tabPage1->Controls->Add(this->textBox2);
			this->tabPage1->Controls->Add(this->progressBar1);
			this->tabPage1->Controls->Add(this->setBtn);
			this->tabPage1->Controls->Add(this->pathBox);
			this->tabPage1->Controls->Add(this->scanBtn);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1096, 514);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Scan";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->bQuarBtn);
			this->tabPage2->Controls->Add(this->quarBtn);
			this->tabPage2->Controls->Add(this->delBtn);
			this->tabPage2->Controls->Add(this->listBox1);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(1096, 514);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Report";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// bQuarBtn
			// 
			this->bQuarBtn->Location = System::Drawing::Point(7, 65);
			this->bQuarBtn->Name = L"bQuarBtn";
			this->bQuarBtn->Size = System::Drawing::Size(176, 23);
			this->bQuarBtn->TabIndex = 3;
			this->bQuarBtn->Text = L"Back form quarantine";
			this->bQuarBtn->UseVisualStyleBackColor = true;
			this->bQuarBtn->Click += gcnew System::EventHandler(this, &MyForm::bQuarBtn_Click);
			// 
			// quarBtn
			// 
			this->quarBtn->Location = System::Drawing::Point(6, 35);
			this->quarBtn->Name = L"quarBtn";
			this->quarBtn->Size = System::Drawing::Size(177, 23);
			this->quarBtn->TabIndex = 2;
			this->quarBtn->Text = L"Quarantine";
			this->quarBtn->UseVisualStyleBackColor = true;
			this->quarBtn->Click += gcnew System::EventHandler(this, &MyForm::quarBtn_Click);
			// 
			// delBtn
			// 
			this->delBtn->Location = System::Drawing::Point(6, 6);
			this->delBtn->Name = L"delBtn";
			this->delBtn->Size = System::Drawing::Size(177, 23);
			this->delBtn->TabIndex = 1;
			this->delBtn->Text = L"Delete";
			this->delBtn->UseVisualStyleBackColor = true;
			this->delBtn->Click += gcnew System::EventHandler(this, &MyForm::delBtn_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"vcxvcx", L"dsf", L"dsa" });
			this->listBox1->Location = System::Drawing::Point(189, 0);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(907, 511);
			this->listBox1->TabIndex = 0;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->mRemMon);
			this->tabPage3->Controls->Add(this->mAddBtn);
			this->tabPage3->Controls->Add(this->mPathBox);
			this->tabPage3->Controls->Add(this->mPath);
			this->tabPage3->Controls->Add(this->listBox2);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(1096, 514);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Monitoring";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// mRemMon
			// 
			this->mRemMon->Location = System::Drawing::Point(4, 90);
			this->mRemMon->Name = L"mRemMon";
			this->mRemMon->Size = System::Drawing::Size(233, 23);
			this->mRemMon->TabIndex = 4;
			this->mRemMon->Text = L"Remove from Monitor";
			this->mRemMon->UseVisualStyleBackColor = true;
			this->mRemMon->Click += gcnew System::EventHandler(this, &MyForm::mRemMon_Click);
			// 
			// mAddBtn
			// 
			this->mAddBtn->Location = System::Drawing::Point(4, 60);
			this->mAddBtn->Name = L"mAddBtn";
			this->mAddBtn->Size = System::Drawing::Size(233, 23);
			this->mAddBtn->TabIndex = 3;
			this->mAddBtn->Text = L"Add to monitor";
			this->mAddBtn->UseVisualStyleBackColor = true;
			this->mAddBtn->Click += gcnew System::EventHandler(this, &MyForm::mAddBtn_Click);
			// 
			// mPathBox
			// 
			this->mPathBox->Location = System::Drawing::Point(4, 4);
			this->mPathBox->Name = L"mPathBox";
			this->mPathBox->Size = System::Drawing::Size(233, 20);
			this->mPathBox->TabIndex = 2;
			// 
			// mPath
			// 
			this->mPath->Location = System::Drawing::Point(4, 30);
			this->mPath->Name = L"mPath";
			this->mPath->Size = System::Drawing::Size(233, 23);
			this->mPath->TabIndex = 1;
			this->mPath->Text = L"Set path";
			this->mPath->UseVisualStyleBackColor = true;
			this->mPath->Click += gcnew System::EventHandler(this, &MyForm::mPath_Click);
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Location = System::Drawing::Point(243, 0);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(850, 511);
			this->listBox2->TabIndex = 0;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->sSendSchBtn);
			this->tabPage4->Controls->Add(this->sRemSch);
			this->tabPage4->Controls->Add(this->listBox3);
			this->tabPage4->Controls->Add(this->textBox3);
			this->tabPage4->Controls->Add(this->sPathBox);
			this->tabPage4->Controls->Add(this->aSchBtn);
			this->tabPage4->Controls->Add(this->sPathBtn);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(1096, 514);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Schedule";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// sSendSchBtn
			// 
			this->sSendSchBtn->Location = System::Drawing::Point(4, 156);
			this->sSendSchBtn->Name = L"sSendSchBtn";
			this->sSendSchBtn->Size = System::Drawing::Size(287, 23);
			this->sSendSchBtn->TabIndex = 7;
			this->sSendSchBtn->Text = L"Admit schedule";
			this->sSendSchBtn->UseVisualStyleBackColor = true;
			this->sSendSchBtn->Click += gcnew System::EventHandler(this, &MyForm::sSendSchBtn_Click);
			// 
			// sRemSch
			// 
			this->sRemSch->Location = System::Drawing::Point(4, 126);
			this->sRemSch->Name = L"sRemSch";
			this->sRemSch->Size = System::Drawing::Size(287, 23);
			this->sRemSch->TabIndex = 6;
			this->sRemSch->Text = L"Remove from Schedule";
			this->sRemSch->UseVisualStyleBackColor = true;
			this->sRemSch->Click += gcnew System::EventHandler(this, &MyForm::sRemSch_Click);
			// 
			// listBox3
			// 
			this->listBox3->FormattingEnabled = true;
			this->listBox3->Location = System::Drawing::Point(298, 15);
			this->listBox3->Name = L"listBox3";
			this->listBox3->Size = System::Drawing::Size(795, 498);
			this->listBox3->TabIndex = 5;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(4, 70);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 4;
			this->textBox3->Text = L"00:00";
			// 
			// sPathBox
			// 
			this->sPathBox->Location = System::Drawing::Point(4, 15);
			this->sPathBox->Name = L"sPathBox";
			this->sPathBox->Size = System::Drawing::Size(287, 20);
			this->sPathBox->TabIndex = 3;
			// 
			// aSchBtn
			// 
			this->aSchBtn->Location = System::Drawing::Point(4, 96);
			this->aSchBtn->Name = L"aSchBtn";
			this->aSchBtn->Size = System::Drawing::Size(287, 23);
			this->aSchBtn->TabIndex = 2;
			this->aSchBtn->Text = L"Add to Schedule";
			this->aSchBtn->UseVisualStyleBackColor = true;
			this->aSchBtn->Click += gcnew System::EventHandler(this, &MyForm::aSchBtn_Click);
			// 
			// sPathBtn
			// 
			this->sPathBtn->Location = System::Drawing::Point(3, 41);
			this->sPathBtn->Name = L"sPathBtn";
			this->sPathBtn->Size = System::Drawing::Size(288, 23);
			this->sPathBtn->TabIndex = 1;
			this->sPathBtn->Text = L"Set path";
			this->sPathBtn->UseVisualStyleBackColor = true;
			this->sPathBtn->Click += gcnew System::EventHandler(this, &MyForm::sPathBtn_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1128, 556);
			this->Controls->Add(this->tabControl1);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void setBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			pathBox->Text = folderBrowserDialog1->SelectedPath;;
		}
	}
	void connectFront()
	{
		CloseHandle(pipe);
		/*переписать когда сервис заработает*/
		while (pipe==INVALID_HANDLE_VALUE || pipe == NULL)
		{
			pipe = CreateFile(
				L"\\\\.\\pipe\\AntimalwarePipe", GENERIC_READ | GENERIC_WRITE,
				0, NULL, OPEN_EXISTING, 0, NULL);
		}
		if (pipeIO)
			pipeIO->setPipe(pipe, 1024);
		else
			pipeIO = new Messanger(pipe, 1024);
	}
	void connectBack()
	{
		CloseHandle(pipeBack);
		pipeBack = CreateNamedPipe(
			L"\\\\.\\pipe\\AntimalwarePipeBack",
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			4096, 4096, 5000, NULL);
		ConnectNamedPipe(pipeBack, NULL);
		if (pipeBackIO)
			pipeBackIO->setPipe(pipeBackIO, 1024);
		else
			pipeBackIO = new Messanger(pipeBack, 1024);
	}
	void backgroundReader()
	{
		connectBack();
		while (true)
		{
			if (pipeBack == INVALID_HANDLE_VALUE)
				connectBack();
			auto t = pipeBackIO->getMSG();
		}
	}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) 
{
	System::Threading::Thread^ connectThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::connectFront));
	connectThread->IsBackground = true;
	connectThread->Start();
	
	backThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::backgroundReader));
	backThread->IsBackground = true;
	backThread->Start();
}
private: System::Void scanBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (pathBox->Text->Length)
	{
		std::string folder = msclr::interop::marshal_as<std::string>(pathBox->Text);
		pipeIO->sendStartMSG(folder);
	}
}
private: System::Void stopSCBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	pipeIO->sendStopMSG();
}
private: System::Void delBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	std::size_t id = listBox1->SelectedIndex;
	if (id!=-1)
		pipeIO->sendValue(Command::DELETE_FILE, id);
}
private: System::Void quarBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	std::size_t id = listBox1->SelectedIndex;
	if (id != -1)
		pipeIO->sendValue(Command::MOV_TO_QUAR, id);
}
private: System::Void mAddBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (mPathBox->Text->Length)
	{
		listBox2->Items->Add(mPathBox->Text);
		std::string folder = msclr::interop::marshal_as<std::string>(mPathBox->Text);
		pipeIO->sendCharArray(Command::ADD_MONIT, folder);
	}
}
private: System::Void mPath_Click(System::Object^ sender, System::EventArgs^ e) {
	if (folderBrowserDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		mPathBox->Text = folderBrowserDialog2->SelectedPath;;
	}
}
private: System::Void mRemMon_Click(System::Object^ sender, System::EventArgs^ e) {
	std::size_t id = listBox2->SelectedIndex;
	if (id != -1)
	{
		pipeIO->sendValue(Command::REM_MONIT, id);
		listBox2->Items->RemoveAt(id);
	}
	
}
private: System::Void sPathBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (folderBrowserDialog3->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		sPathBox->Text = folderBrowserDialog3->SelectedPath;;
	}
}
private: System::Void aSchBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (sPathBox->Text->Length && textBox3->Text->Length)
	{
		listBox3->Items->Add(sPathBox->Text+" "+textBox3->Text);
	}
}
private: System::Void sRemSch_Click(System::Object^ sender, System::EventArgs^ e) {
	std::size_t id = listBox3->SelectedIndex;
	if (id != -1)
	{
		listBox3->Items->RemoveAt(id);
	}
}
private: System::Void sSendSchBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	std::vector<std::string> str;
	for (size_t i = 0; i < listBox3->Items->Count; ++i)
	{
		str.emplace_back(msclr::interop::marshal_as<std::string>(listBox3->Items[i]->ToString()));
	}
	pipeIO->sendCharArray(Command::SCHEDUL, str);
}
private: System::Void bQuarBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	std::size_t id = listBox1->SelectedIndex;
	if (id != -1)
		pipeIO->sendValue(Command::BACK_FROM_QUAR, id);
}
};
}
