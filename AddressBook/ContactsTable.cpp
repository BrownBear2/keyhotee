#include "ContactsTable.hpp"
#include "ui_ContactsTable.h"
#include "AddressBookModel.hpp"
#include <bts/application.hpp>
#include <bts/profile.hpp>

#include <QSortFilterProxyModel>
#include <QHeaderView>

ContactsTable::ContactsTable( QWidget* parent )
: QWidget(parent), 
  ui( new Ui::ContactsTable() )
{
  ui->setupUi(this); 
  _delete_contact = new QAction(this); //QIcon( ":/images/delete_icon.png"), tr( "Delete" ), this);
  _delete_contact->setShortcut(Qt::Key_Delete);
  addAction(_delete_contact);

  connect( _delete_contact, &QAction::triggered, this, &ContactsTable::onDeleteContact);
}

ContactsTable::~ContactsTable(){}

void ContactsTable::setAddressBook( AddressBookModel* addressbook_model )
{
  _addressbook_model = addressbook_model;
  if( _addressbook_model )
  {
     _sorted_addressbook_model = new QSortFilterProxyModel( this );
     _sorted_addressbook_model->setSourceModel( _addressbook_model );
     _sorted_addressbook_model->setDynamicSortFilter(true);
     ui->contact_table->setModel( _sorted_addressbook_model );
  }
  ui->contact_table->setShowGrid(false);
  ui->contact_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  ui->contact_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

  connect( ui->contact_table, &QAbstractItemView::activated, this, &ContactsTable::openContact );
}

void ContactsTable::openContact( const QModelIndex& index )
{
   QModelIndex mapped_index = _sorted_addressbook_model->mapToSource(index);
   auto contact_id = _addressbook_model->getContact(mapped_index).wallet_index;
   Q_EMIT contactOpened( contact_id );
}

void ContactsTable::onDeleteContact()
{
   //remove selected contacts from inbox model (and database)
   QSortFilterProxyModel* model = dynamic_cast<QSortFilterProxyModel*>(ui->contact_table->model());
   //model->setUpdatesEnabled(false);
   QItemSelectionModel* selection_model = ui->contact_table->selectionModel();
   QModelIndexList sortFilterIndexes = selection_model->selectedRows();
   QModelIndexList indexes;
   foreach(QModelIndex sortFilterIndex,sortFilterIndexes)
     indexes.append(model->mapToSource(sortFilterIndex));
   qSort(indexes);
   auto sourceModel = model->sourceModel();
   for(int i = indexes.count() - 1; i > -1; --i)
       sourceModel->removeRows(indexes.at(i).row(),1);
   //model->setUpdatesEnabled(true);   

   //TODO Remove fullname/bitname for deleted contacts from QCompleter
}
