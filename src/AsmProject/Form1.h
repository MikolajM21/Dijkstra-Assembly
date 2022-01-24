/*
JÊZYKI ASEMBLEROWE
Projekt: Alogrytm Dijkstry
Wyznacza najkrótsz¹ trasê miêdzy zadanymi miastami (wierzcho³kami grafu)
Miko³aj Malich
Rok akademicki 2021/2022
*/

#pragma once
#include "projectAsm.h"
#include <msclr\marshal_cppstd.h>

namespace DijkstraAssembly {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	public ref class Form1 : public System::Windows::Forms::Form
	{
		public:
			Form1(void)
			{
				InitializeComponent();
			}

		protected:
			~Form1()
			{
				if (components)
				{
					delete components;
				}
			}

		private: System::Windows::Forms::Label^ inputNo1;
		private: System::Windows::Forms::Button^ roadsButton;
		private: System::Windows::Forms::Label^ roadsLabel;
		private: System::Windows::Forms::RadioButton^ cppButton;
		private: System::Windows::Forms::RadioButton^ asmButton;
		private: System::Windows::Forms::Label^ inputNo2;
		private: System::Windows::Forms::Button^ pathsButton;
		private: System::Windows::Forms::Label^ pathsLabel;
		private: System::Windows::Forms::Label^ outfileLabel;
		private: System::Windows::Forms::Button^ outfileButton;
		private: System::Windows::Forms::Label^ inputNo3;
		private: System::Windows::Forms::Label^ langLabel;
		private: System::Windows::Forms::Label^ threadsLabel;
		private: System::Windows::Forms::TrackBar^ threadsBar;
		private: System::Windows::Forms::Button^ startButton;
		private: System::Windows::Forms::Label^ timeLabel;

		private:
			bool file1, file2, file3 = false;
			System::ComponentModel::Container ^components;

		#pragma region Windows Form Designer generated code
		
			void InitializeComponent(void)
			{
				this->inputNo1 = (gcnew System::Windows::Forms::Label());
				this->roadsButton = (gcnew System::Windows::Forms::Button());
				this->roadsLabel = (gcnew System::Windows::Forms::Label());
				this->cppButton = (gcnew System::Windows::Forms::RadioButton());
				this->asmButton = (gcnew System::Windows::Forms::RadioButton());
				this->inputNo2 = (gcnew System::Windows::Forms::Label());
				this->pathsButton = (gcnew System::Windows::Forms::Button());
				this->pathsLabel = (gcnew System::Windows::Forms::Label());
				this->outfileLabel = (gcnew System::Windows::Forms::Label());
				this->outfileButton = (gcnew System::Windows::Forms::Button());
				this->inputNo3 = (gcnew System::Windows::Forms::Label());
				this->langLabel = (gcnew System::Windows::Forms::Label());
				this->threadsLabel = (gcnew System::Windows::Forms::Label());
				this->threadsBar = (gcnew System::Windows::Forms::TrackBar());
				this->startButton = (gcnew System::Windows::Forms::Button());
				this->timeLabel = (gcnew System::Windows::Forms::Label());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadsBar))->BeginInit();
				this->SuspendLayout();
				// 
				// inputNo1
				// 
				this->inputNo1->AutoSize = true;
				this->inputNo1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(238)));
				this->inputNo1->Location = System::Drawing::Point(17, 16);
				this->inputNo1->Name = L"inputNo1";
				this->inputNo1->Size = System::Drawing::Size(18, 16);
				this->inputNo1->TabIndex = 0;
				this->inputNo1->Text = L"1.";
				this->inputNo1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				// 
				// roadsButton
				// 
				this->roadsButton->Location = System::Drawing::Point(41, 12);
				this->roadsButton->Name = L"roadsButton";
				this->roadsButton->Size = System::Drawing::Size(94, 25);
				this->roadsButton->TabIndex = 1;
				this->roadsButton->Text = L"Select roads file";
				this->roadsButton->UseVisualStyleBackColor = true;
				this->roadsButton->Click += gcnew System::EventHandler(this, &Form1::roadsButton_Click);
				// 
				// roadsLabel
				// 
				this->roadsLabel->AutoSize = true;
				this->roadsLabel->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(238)));
				this->roadsLabel->Location = System::Drawing::Point(141, 16);
				this->roadsLabel->Name = L"roadsLabel";
				this->roadsLabel->Size = System::Drawing::Size(110, 16);
				this->roadsLabel->TabIndex = 2;
				this->roadsLabel->Text = L"No file selected";
				this->roadsLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				// 
				// cppButton
				// 
				this->cppButton->AutoSize = true;
				this->cppButton->Location = System::Drawing::Point(157, 121);
				this->cppButton->Name = L"cppButton";
				this->cppButton->Size = System::Drawing::Size(44, 17);
				this->cppButton->TabIndex = 3;
				this->cppButton->TabStop = true;
				this->cppButton->Text = L"C++";
				this->cppButton->UseVisualStyleBackColor = true;
				this->cppButton->CheckedChanged += gcnew System::EventHandler(this, &Form1::cppButton_CheckedChanged);
				// 
				// asmButton
				// 
				this->asmButton->AutoSize = true;
				this->asmButton->Location = System::Drawing::Point(207, 121);
				this->asmButton->Name = L"asmButton";
				this->asmButton->Size = System::Drawing::Size(44, 17);
				this->asmButton->TabIndex = 4;
				this->asmButton->TabStop = true;
				this->asmButton->Text = L"asm";
				this->asmButton->UseVisualStyleBackColor = true;
				this->asmButton->CheckedChanged += gcnew System::EventHandler(this, &Form1::asmButton_CheckedChanged);
				// 
				// inputNo2
				// 
				this->inputNo2->AutoSize = true;
				this->inputNo2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(238)));
				this->inputNo2->Location = System::Drawing::Point(17, 51);
				this->inputNo2->Name = L"inputNo2";
				this->inputNo2->Size = System::Drawing::Size(18, 16);
				this->inputNo2->TabIndex = 5;
				this->inputNo2->Text = L"2.";
				this->inputNo2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				// 
				// pathsButton
				// 
				this->pathsButton->Location = System::Drawing::Point(41, 47);
				this->pathsButton->Name = L"pathsButton";
				this->pathsButton->Size = System::Drawing::Size(94, 25);
				this->pathsButton->TabIndex = 6;
				this->pathsButton->Text = L"Select paths file";
				this->pathsButton->UseVisualStyleBackColor = true;
				this->pathsButton->Click += gcnew System::EventHandler(this, &Form1::pathsButton_Click);
				// 
				// pathsLabel
				// 
				this->pathsLabel->AutoSize = true;
				this->pathsLabel->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(238)));
				this->pathsLabel->Location = System::Drawing::Point(141, 51);
				this->pathsLabel->Name = L"pathsLabel";
				this->pathsLabel->Size = System::Drawing::Size(110, 16);
				this->pathsLabel->TabIndex = 7;
				this->pathsLabel->Text = L"No file selected";
				this->pathsLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				// 
				// outfileLabel
				// 
				this->outfileLabel->AutoSize = true;
				this->outfileLabel->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(238)));
				this->outfileLabel->Location = System::Drawing::Point(141, 88);
				this->outfileLabel->Name = L"outfileLabel";
				this->outfileLabel->Size = System::Drawing::Size(110, 16);
				this->outfileLabel->TabIndex = 10;
				this->outfileLabel->Text = L"No file selected";
				this->outfileLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				// 
				// outfileButton
				// 
				this->outfileButton->Location = System::Drawing::Point(41, 84);
				this->outfileButton->Name = L"outfileButton";
				this->outfileButton->Size = System::Drawing::Size(94, 25);
				this->outfileButton->TabIndex = 9;
				this->outfileButton->Text = L"Select outfile";
				this->outfileButton->UseVisualStyleBackColor = true;
				this->outfileButton->Click += gcnew System::EventHandler(this, &Form1::outfileButton_Click);
				// 
				// inputNo3
				// 
				this->inputNo3->AutoSize = true;
				this->inputNo3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(238)));
				this->inputNo3->Location = System::Drawing::Point(17, 88);
				this->inputNo3->Name = L"inputNo3";
				this->inputNo3->Size = System::Drawing::Size(18, 16);
				this->inputNo3->TabIndex = 8;
				this->inputNo3->Text = L"3.";
				this->inputNo3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				// 
				// langLabel
				// 
				this->langLabel->AutoSize = true;
				this->langLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(238)));
				this->langLabel->Location = System::Drawing::Point(17, 121);
				this->langLabel->Name = L"langLabel";
				this->langLabel->Size = System::Drawing::Size(134, 16);
				this->langLabel->TabIndex = 11;
				this->langLabel->Text = L"4.    Select language: ";
				// 
				// threadsLabel
				// 
				this->threadsLabel->AutoSize = true;
				this->threadsLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(238)));
				this->threadsLabel->Location = System::Drawing::Point(17, 156);
				this->threadsLabel->Name = L"threadsLabel";
				this->threadsLabel->Size = System::Drawing::Size(192, 16);
				this->threadsLabel->TabIndex = 12;
				this->threadsLabel->Text = L"5.    Number of threads:              1";
				// 
				// threadsBar
				// 
				this->threadsBar->Location = System::Drawing::Point(20, 184);
				this->threadsBar->Maximum = 64;
				this->threadsBar->Minimum = 1;
				this->threadsBar->Name = L"threadsBar";
				this->threadsBar->Size = System::Drawing::Size(231, 45);
				this->threadsBar->TabIndex = 13;
				this->threadsBar->Value = 1;
				this->threadsBar->Scroll += gcnew System::EventHandler(this, &Form1::threadsBar_Scroll);
				// 
				// startButton
				// 
				this->startButton->Location = System::Drawing::Point(20, 236);
				this->startButton->Name = L"startButton";
				this->startButton->Size = System::Drawing::Size(231, 39);
				this->startButton->TabIndex = 14;
				this->startButton->Text = L"Run application";
				this->startButton->UseVisualStyleBackColor = true;
				this->startButton->Click += gcnew System::EventHandler(this, &Form1::startButton_Click);
				// 
				// timeLabel
				// 
				this->timeLabel->AutoSize = true;
				this->timeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(238)));
				this->timeLabel->Location = System::Drawing::Point(98, 288);
				this->timeLabel->Name = L"timeLabel";
				this->timeLabel->Size = System::Drawing::Size(70, 16);
				this->timeLabel->TabIndex = 15;
				this->timeLabel->Text = L"Time: 0ms";
				// 
				// Form1
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(269, 325);
				this->Controls->Add(this->timeLabel);
				this->Controls->Add(this->startButton);
				this->Controls->Add(this->threadsBar);
				this->Controls->Add(this->threadsLabel);
				this->Controls->Add(this->langLabel);
				this->Controls->Add(this->outfileLabel);
				this->Controls->Add(this->outfileButton);
				this->Controls->Add(this->inputNo3);
				this->Controls->Add(this->pathsLabel);
				this->Controls->Add(this->pathsButton);
				this->Controls->Add(this->inputNo2);
				this->Controls->Add(this->asmButton);
				this->Controls->Add(this->cppButton);
				this->Controls->Add(this->roadsLabel);
				this->Controls->Add(this->roadsButton);
				this->Controls->Add(this->inputNo1);
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				this->MaximizeBox = false;
				this->MinimizeBox = false;
				this->Name = L"Form1";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->Text = L"Dijkstra Algorithm";
				this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadsBar))->EndInit();
				this->ResumeLayout(false);
				this->PerformLayout();
			}
		#pragma endregion

		private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
			threadsNr = std::thread::hardware_concurrency();
			threadsLabel->Text = "5.    Number of threads:             " + threadsNr;
		}
		private: System::Void roadsButton_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void pathsButton_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void outfileButton_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void cppButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		private: System::Void asmButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		private: System::Void threadsBar_Scroll(System::Object^ sender, System::EventArgs^ e);
		private: System::Void startButton_Click(System::Object^ sender, System::EventArgs^ e);
	};
}