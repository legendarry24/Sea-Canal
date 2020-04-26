#pragma once
#include "Ship.h"

namespace WinFormsC 
{
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Threading;

	public ref class SeaCanal : public System::Windows::Forms::Form
	{
		public:
			SeaCanal()
			{
				InitializeComponent();
			}

		private:
			const int canalX = 600;
			const int canalWidth = 500;
			
			List<Ship^>^ ships = gcnew List<Ship^>;
			Object^ lock = gcnew Object;

		private: System::Windows::Forms::Button^  createShipBtn;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->createShipBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// createShipBtn
			// 
			this->createShipBtn->BackColor = System::Drawing::Color::Chartreuse;
			this->createShipBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.818182F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->createShipBtn->Location = System::Drawing::Point(971, 603);
			this->createShipBtn->Name = L"createShipBtn";
			this->createShipBtn->Size = System::Drawing::Size(121, 39);
			this->createShipBtn->TabIndex = 4;
			this->createShipBtn->Text = L"Create Ship";
			this->createShipBtn->UseVisualStyleBackColor = false;
			this->createShipBtn->Click += gcnew System::EventHandler(this, &SeaCanal::createShipBtn_Click);
			// 
			// SeaCanal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1700, 683);
			this->Controls->Add(this->createShipBtn);
			this->DoubleBuffered = true;
			this->Name = L"SeaCanal";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sea Canal";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &SeaCanal::SeaCanal_Paint);
			this->ResumeLayout(false);
		}
#pragma endregion

		private: void createShipBtn_Click(Object^ sender, EventArgs^ e) 
		{
			Ship^ ship = gcnew Ship(0, 400);
			ships->Add(ship);

			Thread^ thread = gcnew Thread(gcnew ParameterizedThreadStart(this, &SeaCanal::Run));
			thread->Start(ship);
		}

		private: void SeaCanal_Paint(Object^ sender, PaintEventArgs^ e)
		{
			Graphics^ g = e->Graphics;

			// Draw a sea
			g->FillRectangle(Brushes::DeepSkyBlue, 0, 80, Form::Size.Width, Form::Size.Height - 80);

			// Draw a canal
			g->FillRectangle(Brushes::SandyBrown, canalX, 80, canalWidth, Form::Size.Height - 80);
			g->FillRectangle(Brushes::DodgerBlue, canalX, 300, canalWidth, 150);
		}

		protected: void OnPaint(PaintEventArgs^ e) override
		{
			Form::OnPaint(e);
			Graphics^ g = e->Graphics;

			for each (Ship^ ship in ships)
			{
				ship->Draw(g);
			}
		}

		private: void Run(Object^ obj)
		{
			Ship^ ship = safe_cast<Ship^>(obj);

			int dx = 20;
			const int timeToGoThroughTheCanal = canalWidth / dx;

			while (true)
			{
				if (!ship->IsReadyToEnterTheCanal(canalX, canalWidth))
				{
					ship->Move(dx);

					if (ship->GetX() > Form::Size.Width || ship->GetX() < 0)
					{
						ship->ChangeDirection();
						dx = -dx;
					}

					Invalidate();
					Thread::Sleep(50);
				}
				else
				{
					Monitor::Enter(lock);

					for (int i = timeToGoThroughTheCanal - 1; i >= 0; i--)
					{
						ship->Move(dx);

						Invalidate();
						Thread::Sleep(50);
					}

					Monitor::Exit(lock);
				}
			}
		}
	};
}