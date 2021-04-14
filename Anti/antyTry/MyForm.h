#pragma once
#include"DataIO.h"
#include <algorithm>
#include <string>
#include <vector>
#include <msclr/marshal_cppstd.h>
#include <thread>
namespace antyTry {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			Control::CheckForIllegalCrossThreadCalls = false;
			dw = new DataIO::DataWriter();
			dr = new DataIO::DataReader();
		}

	protected:
		
		~MyForm()
		{
			if (components)
			{
				delete components;
				delete dw;
				delete dr;
			}
			
			
		}
	private: DataIO::DataWriter *dw;
	private: DataIO::DataReader* dr;
	private: System::Windows::Forms::DataGridView^ dataGridView1;







	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ pathBox;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::DataGridView^ dataGridView2;





	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column8;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column7;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column6;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ aType;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ aName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ aSign;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ aOffS;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ aOffE;














	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pathBox = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->aType = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->aName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->aSign = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->aOffS = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->aOffE = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button5 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {
				this->Column1,
					this->Column2, this->Column8, this->Column7, this->Column3, this->Column4, this->Column5, this->Column6
			});
			this->dataGridView1->Location = System::Drawing::Point(13, 12);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(950, 280);
			this->dataGridView1->TabIndex = 0;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"№";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Width = 30;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Тype";
			this->Column2->Name = L"Column2";
			this->Column2->Width = 50;
			// 
			// Column8
			// 
			this->Column8->HeaderText = L"Name_";
			this->Column8->Name = L"Column8";
			// 
			// Column7
			// 
			this->Column7->HeaderText = L"Signature";
			this->Column7->Name = L"Column7";
			this->Column7->Width = 200;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Signature length";
			this->Column3->Name = L"Column3";
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Start Offset";
			this->Column4->Name = L"Column4";
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"End Offset";
			this->Column5->Name = L"Column5";
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"SHA256";
			this->Column6->Name = L"Column6";
			this->Column6->Width = 325;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(224, 549);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(206, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Set Path";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// pathBox
			// 
			this->pathBox->Enabled = false;
			this->pathBox->Location = System::Drawing::Point(12, 518);
			this->pathBox->Name = L"pathBox";
			this->pathBox->Size = System::Drawing::Size(951, 20);
			this->pathBox->TabIndex = 2;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(436, 549);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(206, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Load Data";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(12, 549);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(206, 23);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Create Data";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Binary files (*.bin)|*.bin";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(12, 327);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(206, 23);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Add Record";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToAddRows = false;
			this->dataGridView2->AllowUserToDeleteRows = false;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->aType,
					this->aName, this->aSign, this->aOffS, this->aOffE
			});
			this->dataGridView2->Location = System::Drawing::Point(13, 356);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->Size = System::Drawing::Size(950, 59);
			this->dataGridView2->TabIndex = 6;
			// 
			// aType
			// 
			this->aType->HeaderText = L"Type";
			this->aType->Name = L"aType";
			// 
			// aName
			// 
			this->aName->HeaderText = L"Name";
			this->aName->Name = L"aName";
			// 
			// aSign
			// 
			this->aSign->HeaderText = L"Signature";
			this->aSign->Name = L"aSign";
			this->aSign->Width = 150;
			// 
			// aOffS
			// 
			this->aOffS->HeaderText = L"Start Offset";
			this->aOffS->Name = L"aOffS";
			// 
			// aOffE
			// 
			this->aOffE->HeaderText = L"End Offset";
			this->aOffE->Name = L"aOffE";
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(13, 298);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(206, 23);
			this->button5->TabIndex = 7;
			this->button5->Text = L"Remove Record";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(975, 582);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pathBox);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(2);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private:
	void rewrite()
	{
		auto index = dataGridView1->CurrentCell->RowIndex;
		if (index == -1)
			return;
		DataIO::createData(msclr::interop::marshal_as<std::string>(pathBox->Text));
		size_t size = (dataGridView1->RowCount)-1;
		dw->setPath(msclr::interop::marshal_as<std::string>(pathBox->Text));
		for (size_t i = 0; i < size; ++i)
		{
			if (i == index)
				continue;
			DataIO::Record r;
			r.hash.resize(DataIO::hashSize);
			r.name.resize(DataIO::nameSize);
			r.hash = msclr::interop::marshal_as<std::string>((String^)dataGridView1->Rows[i]->Cells[7]->Value);
			r.name = msclr::interop::marshal_as<std::string>((String^)dataGridView1->Rows[i]->Cells[2]->Value);
			r.offsetEnd = Convert::ToInt32(dataGridView1->Rows[i]->Cells[6]->Value);
			r.offsetStart = Convert::ToInt32(dataGridView1->Rows[i]->Cells[5]->Value);
			r.signSize = Convert::ToInt32(dataGridView1->Rows[i]->Cells[4]->Value);
			if (dataGridView1->Rows[i]->Cells[1]->Value == "exe")
				r.type = DataIO::FILETYPE::EXE;
			else if (dataGridView1->Rows[i]->Cells[1]->Value == "zip")
				r.type = DataIO::FILETYPE::ZIP;
			else 
				r.type = DataIO::FILETYPE::UNKNOWN;
			std::string tempV = msclr::interop::marshal_as<std::string>((String^)dataGridView1->Rows[i]->Cells[3]->Value);
			std::memcpy(&r.signature, tempV.data(), sizeof(r.signature));
			dw->writeInRec(r);
		}
		delete dr;
		dr = new DataIO::DataReader();
		dataGridView1->Rows->Clear();
		readData();
	}
	void addRecord()
	{
		dw->setPath(msclr::interop::marshal_as<std::string>(pathBox->Text));
		std::vector<std::string> arr;
		arr.resize(5);
		for (size_t i = 0; i < arr.size(); ++i)
			arr.at(i) = msclr::interop::marshal_as<std::string>((String^)dataGridView2->Rows[0]->Cells[i]->Value);
		for (auto& el : arr)
			if (el.empty())
				return;
		DataIO::FILETYPE ft;
		if (arr[0] == "zip")
			ft = DataIO::FILETYPE::ZIP;
		else if (arr[0] == "exe")
			ft = DataIO::FILETYPE::EXE;
		else
			ft = DataIO::FILETYPE::UNKNOWN;
		if (dw->writeIn(arr[2], arr[1], std::stoi(arr[3]), std::stoi(arr[4]), ft))
		{
			dataGridView1->Rows->Clear();
			readData();
		}
		dataGridView2->Rows->Clear();
		dataGridView2->RowCount = 1;
	}
	void readData()
	{
		dr->setPath(msclr::interop::marshal_as<std::string>(pathBox->Text));
		std::optional<DataIO::Record> res = std::nullopt;
		std::string sign;
		int i = dataGridView1->RowCount-1;
		while ((res = dr->readNext()).has_value())
		{
			sign.clear();
			sign.resize(sizeof(uint64_t));
			dataGridView1->Rows->Add();
			dataGridView1->Rows[i]->Cells[0]->Value = i+1;
			switch (res.value().type)
			{
			case DataIO::FILETYPE::EXE:
				dataGridView1->Rows[i]->Cells[1]->Value = "exe";
				break;
			case DataIO::FILETYPE::ZIP:
				dataGridView1->Rows[i]->Cells[1]->Value = "zip";
				break;
			default:
				dataGridView1->Rows[i]->Cells[1]->Value = "?";
				break;
			}
			//dataGridView1->Rows[i]->Cells[1]->Value = (int)res.value().type;
			dataGridView1->Rows[i]->Cells[2]->Value = msclr::interop::marshal_as<String^>(res.value().name);
			std::memcpy(sign.data(), &res.value().signature, sizeof(uint64_t));
			dataGridView1->Rows[i]->Cells[3]->Value = msclr::interop::marshal_as<String^>(sign);
			dataGridView1->Rows[i]->Cells[4]->Value = (int)res.value().signSize;
			dataGridView1->Rows[i]->Cells[5]->Value = (int)res.value().offsetStart;
			dataGridView1->Rows[i]->Cells[6]->Value = (int)res.value().offsetEnd;
			dataGridView1->Rows[i]->Cells[7]->Value = msclr::interop::marshal_as<String^>(res.value().hash);
			++i;	
		}
	}
	void createData()
	{
		std::string path = DataIO::createData();
		pathBox->Text = msclr::interop::marshal_as<String^>(path);
	}
	
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		pathBox->Text = openFileDialog1->FileName;
		dataGridView1->Rows->Clear();
	}
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) 
{
	System::Threading::Thread^ th = gcnew Thread(gcnew ThreadStart(this, &MyForm::createData));
	th->IsBackground = true;
	th->Start();
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	
	if (pathBox->Text->Length)
	{
		System::Threading::Thread^ th = gcnew Thread(gcnew ThreadStart(this, &MyForm::addRecord));
		th->IsBackground = true;
		th->Start();
	}
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (pathBox->Text->Length)
	{
		delete dr;
		dr = new DataIO::DataReader();
		dataGridView1->Rows->Clear();
		System::Threading::Thread^ th = gcnew Thread(gcnew ThreadStart(this, &MyForm::readData));
		th->IsBackground = true;
		th->Start();
	}
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Threading::Thread^ th = gcnew Thread(gcnew ThreadStart(this, &MyForm::rewrite));
	th->IsBackground = true;
	th->Start();
}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	this->dataGridView2->RowCount = 1;
}
};
}
