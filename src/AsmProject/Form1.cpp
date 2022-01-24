/*
JÊZYKI ASEMBLEROWE
Projekt: Alogrytm Dijkstry
Wyznacza najkrótsz¹ trasê miêdzy zadanymi miastami (wierzcho³kami grafu)
Miko³aj Malich
Rok akademicki 2021/2022
*/

#include "pch.h"
#include "Form1.h"

System::Void DijkstraAssembly::Form1::roadsButton_Click(System::Object^ sender, System::EventArgs^ e) 
{
	System::String^ roadsLocation;
	try 
	{
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			roadsLocation = openFileDialog1->FileName;
			String^ fileType = System::IO::Path::GetExtension(roadsLocation);
			if (fileType != ".txt")
			{
				System::Windows::Forms::MessageBox::Show("Error: " + "File type must be .txt",
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			String^ shortName = System::IO::Path::GetFileName(roadsLocation);
			if (shortName->ToString()->Length > 14)
			{
				shortName = shortName->ToString()->Substring(0, 8) + "[..].txt";
			}
			roadsLabel->Text = shortName;
			fileRoads = msclr::interop::marshal_as<std::string>(roadsLocation);
			file1 = true;
		}
	}
	catch (System::Exception^ e) 
	{
		System::Windows::Forms::MessageBox::Show("Error: " + e->Message,
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
System::Void DijkstraAssembly::Form1::pathsButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::String^ pathsLocation;
	try 
	{
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			pathsLocation = openFileDialog1->FileName;
			String^ fileType = System::IO::Path::GetExtension(pathsLocation);
			if (fileType != ".txt")
			{
				System::Windows::Forms::MessageBox::Show("Error: " + "File type must be .txt",
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			String^ shortName = System::IO::Path::GetFileName(pathsLocation);
			if (shortName->ToString()->Length > 14)
			{
				shortName = shortName->ToString()->Substring(0, 8) + "[..].txt";
			}
			pathsLabel->Text = shortName;
			filePaths = msclr::interop::marshal_as<std::string>(pathsLocation);
			file2 = true;
		}
	}
	catch (System::Exception^ e) 
	{
		System::Windows::Forms::MessageBox::Show("Error: " + e->Message, 
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
System::Void DijkstraAssembly::Form1::outfileButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::String^ outfileLocation;
	try 
	{
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			outfileLocation = openFileDialog1->FileName;
			String^ fileType = System::IO::Path::GetExtension(outfileLocation);
			if (fileType != ".txt")
			{
				System::Windows::Forms::MessageBox::Show("Error: " + "File type must be .txt", 
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			String^ shortName = System::IO::Path::GetFileName(outfileLocation);
			if (shortName->ToString()->Length > 14)
			{
				shortName = shortName->ToString()->Substring(0, 8) + "[..].txt";
			}
			outfileLabel->Text = shortName;
			fileResults = msclr::interop::marshal_as<std::string>(outfileLocation);
			file3 = true;
		}
	}
	catch (System::Exception^ e) 
	{
		System::Windows::Forms::MessageBox::Show("Error: " + e->Message, 
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
System::Void DijkstraAssembly::Form1::cppButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	cppDll = true;
	asmDll = false;
}
System::Void DijkstraAssembly::Form1::asmButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	asmDll = true;
	cppDll = false;
}
System::Void DijkstraAssembly::Form1::threadsBar_Scroll(System::Object^ sender, System::EventArgs^ e)
{
	threadsLabel->Text = "5.    Number of threads:             " + threadsBar->Value.ToString();
	threadsNr = threadsBar->Value;
}
System::Void DijkstraAssembly::Form1::startButton_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (file1)
	{
		if (file2)
		{
			if (file3)
			{
				if (cppDll && !asmDll || !cppDll && asmDll)
				{
					switch (runProgram())
					{
						case 0:
						{
							timeLabel->Text = "Time: " + timeCounted + "ms";
							System::Windows::Forms::MessageBox::Show("Program finished!",
								"Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
							const char* convertedResultsPath = fileResults.c_str();
							system(convertedResultsPath);
							break;
						}
						case 1:
						{
							System::Windows::Forms::MessageBox::Show("Error: " +
								"Roads file contains invalid file format", "Error", MessageBoxButtons::OK,
								MessageBoxIcon::Error);
							break;
						}
						case 2:
						{
							System::Windows::Forms::MessageBox::Show("Error: " +
								"Paths file contains invalid file format", "Error", MessageBoxButtons::OK,
								MessageBoxIcon::Error);
							break;
						}
						case 3:
						{
							System::Windows::Forms::MessageBox::Show("Error: " +
								"A problem with outfile occured", "Error", MessageBoxButtons::OK,
								MessageBoxIcon::Error);
							break;
						}
						default:
						{
							System::Windows::Forms::MessageBox::Show("Error: " + "Runtime error occured",
								"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
							break;
						}
					}
				}
				else
				{
					System::Windows::Forms::MessageBox::Show("Error: " + "Language not selected", 
						"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			else
			{
				System::Windows::Forms::MessageBox::Show("Error: " + "Outfile not attached",
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		else
		{
			System::Windows::Forms::MessageBox::Show("Error: " + "Paths file not attached",
				"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	else
	{
		System::Windows::Forms::MessageBox::Show("Error: " + "Roads file not attached",
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}