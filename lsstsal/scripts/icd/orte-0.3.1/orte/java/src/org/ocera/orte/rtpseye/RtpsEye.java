/*
 * NewJFrame.java
 *
 * Created on April 27, 2005, 12:01 PM
 */

package org.ocera.orte.rtpseye;

import org.ocera.orte.types.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.tree.*;

/**
 *
 * @author  pokorl
 */
public class RtpsEye extends javax.swing.JFrame {

    /** Creates new form NewJFrame */
    public RtpsEye() {
         initComponents();                 
         rtpsTree = new RtpsTree(jTree1,jTableAppInfo,jTablePSInfo);
         events = new Events(rtpsTree,jLabelMessage);
         appDomain = new org.ocera.orte.DomainApp(ORTEConstant.ORTE_DEFAULT_DOMAIN,
                                                  DomainProp.defaultPropsCreate(),
                                                  events,
                                                  false);	
        if (appDomain == null)
	{            
            jLabelMessage.setForeground(new java.awt.Color(255,0,0));
            jLabelMessage.setText(" can not create application domain!");            
            return;
	}                        
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    private void initComponents() {//GEN-BEGIN:initComponents
        jSplitPane1 = new javax.swing.JSplitPane();
        jScrollPane1 = new javax.swing.JScrollPane();
        root = ManageTree.createRootNodeByName("searching..");
        jTree1 = new javax.swing.JTree(root);
        // only 1 node in a tree can be selected
        selectionModel = jTree1.getSelectionModel();
        selectionModel.setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
        // add listener
        jTree1.addTreeSelectionListener(new javax.swing.event.TreeSelectionListener() {
            public void valueChanged(javax.swing.event.TreeSelectionEvent selEvent) {
                // attend of the event
                rtpsTree.nodeSelected(selEvent);
            }
        });
        jPanel1 = new javax.swing.JPanel();
        jScrollPane2 = new javax.swing.JScrollPane();
        jTableAppInfo = new javax.swing.JTable();
        jScrollPane3 = new javax.swing.JScrollPane();
        jTablePSInfo = new javax.swing.JTable();
        jPanel2 = new javax.swing.JPanel();
        jButtonExit = new javax.swing.JButton();
        jPanel3 = new javax.swing.JPanel();
        jLabelMessage = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        jSplitPane1.setDividerSize(5);
        jSplitPane1.setAlignmentX(1500.0F);
        jSplitPane1.setPreferredSize(new java.awt.Dimension(600, 320));
        jTree1.setPreferredSize(new java.awt.Dimension(200, 72));
        // /////////////////////////////////////////////////////
        DefaultTreeCellRenderer renderer = new DefaultTreeCellRenderer();
        renderer.setOpenIcon(null);//(customOpenIcon);
        renderer.setClosedIcon(null);//(customClosedIcon);
        renderer.setLeafIcon(null);//(customLeafIcon);
        jTree1.setCellRenderer(renderer);
        // /////////////////////////////////////////////////////
        jScrollPane1.setViewportView(jTree1);

        jSplitPane1.setLeftComponent(jScrollPane1);

        jPanel1.setLayout(new java.awt.BorderLayout());

        jPanel1.setPreferredSize(new java.awt.Dimension(200, 438));
        jScrollPane2.setPreferredSize(new java.awt.Dimension(200, 200));
        jTableAppInfo.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null}
            },
            new String [] {
                "Property", "Current Value"
            }
        ) {
            boolean[] canEdit = new boolean [] {
                false, false
            };

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        jScrollPane2.setViewportView(jTableAppInfo);

        jPanel1.add(jScrollPane2, java.awt.BorderLayout.NORTH);

        jScrollPane3.setPreferredSize(new java.awt.Dimension(453, 70));
        jTablePSInfo.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null},
                {null, null},
                {null, null},
                {null, null}
            },
            new String [] {
                "Property", "Current Value"
            }
        ) {
            boolean[] canEdit = new boolean [] {
                false, false
            };

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        jScrollPane3.setViewportView(jTablePSInfo);

        jPanel1.add(jScrollPane3, java.awt.BorderLayout.CENTER);

        jPanel2.setLayout(new java.awt.BorderLayout());

        jPanel2.setMinimumSize(new java.awt.Dimension(57, 30));
        jPanel2.setPreferredSize(new java.awt.Dimension(200, 20));
        jButtonExit.setText("exit");
        jButtonExit.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonExitActionPerformed(evt);
            }
        });

        jPanel2.add(jButtonExit, java.awt.BorderLayout.EAST);

        jPanel1.add(jPanel2, java.awt.BorderLayout.SOUTH);

        jSplitPane1.setRightComponent(jPanel1);

        getContentPane().add(jSplitPane1, java.awt.BorderLayout.CENTER);

        jPanel3.setLayout(new java.awt.BorderLayout());

        jLabelMessage.setFont(new java.awt.Font("Dialog", 0, 10));
        jLabelMessage.setText(" searching for Rtps communication..");
        jPanel3.add(jLabelMessage, java.awt.BorderLayout.CENTER);

        getContentPane().add(jPanel3, java.awt.BorderLayout.SOUTH);

        pack();
    }//GEN-END:initComponents

    private void jButtonExitActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonExitActionPerformed
        /* TODO add your handling code here: */
        /* TODO  pridat kod na destroy domeny!! */
        this.appDomain.destroy();
        this.dispose();
    }//GEN-LAST:event_jButtonExitActionPerformed
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new RtpsEye().setVisible(true);
            }
        });
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButtonExit;
    private javax.swing.JLabel jLabelMessage;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JSplitPane jSplitPane1;
    private javax.swing.JTable jTableAppInfo;
    private javax.swing.JTable jTablePSInfo;
    private javax.swing.JTree jTree1;
    // End of variables declaration//GEN-END:variables

    
    // my declarations
    private javax.swing.tree.TreeSelectionModel selectionModel;
    private javax.swing.tree.DefaultMutableTreeNode root;
    private org.ocera.orte.rtpseye.RtpsTree rtpsTree; 
    private org.ocera.orte.rtpseye.Events events;
    private org.ocera.orte.DomainApp appDomain;            
    
    private Icon customOpenIcon = new ImageIcon("images/regFail.gif");
    private Icon customClosedIcon = new ImageIcon("images/regFail.gif");
    private Icon customLeafIcon = new ImageIcon("images/regFail.gif");
}